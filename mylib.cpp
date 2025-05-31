#include "mylib.h"

void backgroundSound() {
	PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
}

void StopBackgroundMusic() {
	PlaySound(NULL, NULL, 0);
}

void PlayEatSound() {
	PlaySound(TEXT("eat.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
}

void PlayWinSound() {
	PlaySound(TEXT("winGame.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
}

void PlayButtonSound() {
	PlaySound(TEXT("buttonsound.wav"), NULL, SND_FILENAME | SND_SYNC | SND_NOSTOP);
}

void PlayDeadSound() {
	PlaySound(TEXT("dead.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
}

void fixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void CenterConsoleWindow()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	int consoleWidth = r.right - r.left;
	int consoleHeight = r.bottom - r.top;

	int newX = (screenWidth - consoleWidth) / 2;
	int newY = (screenHeight - consoleHeight) / 2;

	MoveWindow(console, newX, newY, consoleWidth, consoleHeight, TRUE);
}

void ResizeConsoleWindow(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	int consoleWidth = r.right - r.left;
	int consoleHeight = r.bottom - r.top;

	int newWidth = width * 8 + 16;
	int newHeight = height * 12 + 39;

	MoveWindow(console, r.left, r.top, newWidth, newHeight, TRUE);

	COORD bufferSize = { (SHORT)width, (SHORT)(height * 2) };
	SetConsoleScreenBufferSize(console, bufferSize);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void maximizeConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	ShowWindow(consoleWindow, SW_MAXIMIZE);
}

void hideScrollBar() {
	HWND consoleWindow = GetConsoleWindow();
	ShowScrollBar(consoleWindow, SB_BOTH, FALSE);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int backgound_color, int text_color)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int color_code = backgound_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}





void DrawSnake1(const char* str) {
	for (int i = 0; i < SIZE_SNAKE; i++) {
		GotoXY(snake[i].x, snake[i].y);
		cout << str;
	}
}

void DrawSnake() {
	char str;
	int idx = 0;
	char a[] = { '2','3','1','2','0','2','2','8','2','3','1','2','0','2','2','0','2','3','1','2','0','2' ,'1','8','2','3','1','2','0','2' ,'1','6','2','3','1','2','0','2' ,'3','8' };
	for (int i = 0; i < SIZE_SNAKE; i++) {
		GotoXY(snake[i].x, snake[i].y);
		str = a[i];
		idx = i;
		cout << str;
	}
}

void BlinkSnake(int blinkCount, int delayMilliseconds) {
	for (int i = 0; i < blinkCount; i++) {
		if (FOOD_INDEX == MAX_SIZE_FOOD) {
			GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
			cout << (char)201;
		}
		else {
			GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
			cout << (char)3;
		}
		SetColor(4, 15);
		DrawSnake1(" ");
		Sleep(delayMilliseconds);

		DrawSnake();
		Sleep(delayMilliseconds);
		SetColor(15, 4);
	}
}






void printMyFile(const char* fileName) {
	FILE* file = fopen(fileName, "r");
	fseek(file, 0L, SEEK_END);
	long size = ftell(file);
	fseek(file, 0L, SEEK_SET);
	char* buffer = (char*)calloc(size, sizeof(char));
	if (buffer == NULL) {
		return;
	}
	fread(buffer, sizeof(char), size, file);
	fclose(file);
	printf(buffer);
	free(buffer);
}



void writeFileScore(saveScore& saveNameScore, char dname[]) {
	FILE* p;
	if (fopen_s(&p, dname, "w") == 0) {
		fwrite(&saveNameScore, sizeof(struct saveScore), 1, p);
		fclose(p);
	}
	else {
		std::cerr << "Error!" << std::endl;
	}
}

void readFileScore(saveScore& saveNameScore, char dname[]) {
	FILE* p;
	if (fopen_s(&p, dname, "r") == 0) {
		fread(&saveNameScore, sizeof(struct saveScore), 1, p);
		fclose(p);
	}
	else {
		std::cerr << "Error!" << std::endl;
	}
}

void writeFileName(saveNameFile& saveName, char dname[]) {
	FILE* p;
	if (fopen_s(&p, dname, "w") == 0) {
		fwrite(&saveName, sizeof(struct saveNameFile), 1, p);
		fclose(p);
	}
	else {
		std::cerr << "Error!" << std::endl;
	}
}

void readFileName(saveNameFile& saveName, char dname[]) {
	FILE* p;
	if (fopen_s(&p, dname, "r") == 0) {
		fread(&saveName, sizeof(struct saveNameFile), 1, p);
		fclose(p);
	}
	else {
		std::cerr << "Error!" << std::endl;
	}
}

void ghifile(saveSnake luusnake, char dname[]) {
	luusnake.level = LEVEL;
	luusnake.foodIndex = FOOD_INDEX;
	luusnake.food.x = food[FOOD_INDEX].x;
	luusnake.food.y = food[FOOD_INDEX].y;
	luusnake.snakeSize = SIZE_SNAKE;
	luusnake.luuScore = SCORE;
	luusnake.luuCHAR_LOCK = CHAR_LOCK;
	luusnake.luuMOVING = MOVING;
	if (LEVEL == 3) {
		luusnake.obstacle[1].x = obstaclelv3[1].x;
		luusnake.obstacle[0].x = obstaclelv3[0].x;
		luusnake.obstacle[1].y = obstaclelv3[1].y;
		luusnake.obstacle[0].y = obstaclelv3[0].y;
	}
	for (int i = 0; i < SIZE_SNAKE; i++) {
		luusnake.SaveSnake[i] = snake[i];
	}

	FILE* p;
	if (fopen_s(&p, dname, "wb") == 0) {
		fwrite(&luusnake, sizeof(struct saveSnake), 1, p);
		fclose(p);
	}
	else {
		std::cerr << "Error!" << std::endl;
	}
}

bool hasInvalidChars(const char* filename) {
	const char* invalidChars = "\\/:?\"<>|";
	while (*filename) {
		if (strchr(invalidChars, *filename)) {
			return true;
		}
		filename++;
	}
	return false;
}

bool isValidFileName(const char* filename) {
	if (hasInvalidChars(filename)) {
		return false;
	}

	const char* lastSlash = strrchr(filename, '/');
	const char* name = lastSlash ? lastSlash + 1 : filename;
	const char* extension = strrchr(name, '.');
	int nameLength = extension ? extension - name : strlen(name);
	if (nameLength == 0) {
		return false;
	}

	return true;
}

bool checkName(saveNameFile& saveName, const char* text) {
	if (!isValidFileName(text)) return true;
	readFileName(saveName, (char*)nameFile);
	for (int i = 0; i <= saveName.size; i++) {
		const char* temp = saveName.name[i].c_str();
		if (strcmp(temp, text) == 0) return true;
	}
	return false;
}

bool checkNameScore(saveScore& saveNameScore, const char* text) {
	if (!isValidFileName(text)) return true;
	readFileScore(saveNameScore, (char*)nameFile1);
	for (int i = 0; i <= saveNameScore.size; i++) {
		const char* temp = saveNameScore.namePlay[i].c_str();
		if (strcmp(temp, text) == 0) return true;
	}
	return false;
}


void docfile(saveSnake& luusnake, char dname[]) {
	FILE* p;
	if (fopen_s(&p, dname, "rb") == 0) {
		fread(&luusnake, sizeof(struct saveSnake), 1, p);
		fclose(p);
	}
	else {
		std::cerr << "Error!" << std::endl;
	}
}




bool IsValid(int x, int y) {

	for (int i = 0; i < SIZE_SNAKE; i++) {
		if (snake[i].x == x && snake[i].y == y) {
			return false;
		}
	}
	return true;
}

void GenerateFood() {
	int x, y;
	srand(static_cast<unsigned int>(time(NULL)));
	if (LEVEL == 1) {
		for (int i = 0; i < MAX_SIZE_FOOD; i++) {
			do {
				x = rand() % (WIDTH_CONSOLE - 1) + 1;
				y = rand() % (HEIGH_CONSOLE - 1) + 1;
			} while (IsValid(x, y) == false);
			food[i] = { x,y };
		}
	}
	else if (LEVEL == 2) {
		for (int i = 0; i < MAX_SIZE_FOOD; i++) {
			do {
				x = rand() % (WIDTH_CONSOLE - 1) + 1;
				y = rand() % (HEIGH_CONSOLE - 1) + 1;
			} while (IsValid(x, y) == false || checkFoodlv2(x, y) == true);
			food[i] = { x,y };
		}
	}
	else if (LEVEL == 3) {
		for (int i = 0; i < MAX_SIZE_FOOD; i++) {
			do {
				x = rand() % (WIDTH_CONSOLE - 1) + 1;
				y = rand() % (HEIGH_CONSOLE - 1) + 1;
			} while (IsValid(x, y) == false || checkFoodlv3(x, y) == true);
			food[i] = { x,y };
		}
	}
	else if (LEVEL == 4) {
		for (int i = 0; i < MAX_SIZE_FOOD; i++) {
			do {
				x = rand() % (WIDTH_CONSOLE - 1) + 1;
				y = rand() % (HEIGH_CONSOLE - 1) + 1;
			} while (IsValid(x, y) == false || checkFoodlv4(x, y) == true);
			food[i] = { x,y };
		}
	}

}


void ResetData() {
	//Initialize the global values
	CHAR_LOCK = 'A', MOVING = 'D', SPEED = 1; FOOD_INDEX = 0, WIDTH_CONSOLE = 100,
		HEIGH_CONSOLE = 40, SIZE_SNAKE = 4;
	// Initialize default values for snake
	snake[0] = { 1, 5 }; snake[1] = { 2, 5 };
	snake[2] = { 3, 5 }; snake[3] = { 4, 5 };	
	ChangeLevel(1);
}


void DrawBoard(int x, int y, int width, int height) {
	SetColor(15, 4);
	for (int i = 1; i < width; i++) {
		GotoXY(i, 0);
		cout << (char)205;
		GotoXY(i, height);
		cout << (char)205;
	}
	for (int i = 1; i < height; i++) {
		GotoXY(0, i);
		cout << (char)186;
		GotoXY(width, i);
		cout << (char)186;
	}
	GotoXY(0, 0); cout << (char)201;
	GotoXY(0, height); cout << (char)200;
	GotoXY(width, 0); cout << (char)187;
	GotoXY(width, height); cout << (char)188;
	GotoXY(150, 40);
}

void DrawMaplv2() {

	system("cls");
	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
	SetColor(15, 10);
	for (int i = (WIDTH_CONSOLE / 2) - 20; i <= (WIDTH_CONSOLE / 2) + 20; i++) {
		GotoXY(i, HEIGH_CONSOLE / 2);
		cout << (char)254;
		ObstacleXlv2[idxObstaclelv2].x = i;
		ObstacleXlv2[idxObstaclelv2].y = HEIGH_CONSOLE / 2;
		idxObstaclelv2++;
	}

	for (int i = HEIGH_CONSOLE / 2 - 10; i <= HEIGH_CONSOLE / 2 + 10; i++) {
		GotoXY(WIDTH_CONSOLE / 2 - 30, i);
		cout << (char)219;
		ObstacleXlv2[idxObstaclelv2].x = WIDTH_CONSOLE / 2 - 30;
		ObstacleXlv2[idxObstaclelv2].y = i;
		idxObstaclelv2++;
	}
	for (int i = HEIGH_CONSOLE / 2 - 10; i <= HEIGH_CONSOLE / 2 + 10; i++) {
		GotoXY(WIDTH_CONSOLE / 2 + 30, i);
		cout << (char)219;
		ObstacleXlv2[idxObstaclelv2].x = WIDTH_CONSOLE / 2 + 30;
		ObstacleXlv2[idxObstaclelv2].y = i;
		idxObstaclelv2++;
	}
	GotoXY((WIDTH_CONSOLE / 2), HEIGH_CONSOLE / 2 + 1);
	for (int i = HEIGH_CONSOLE / 2 + 1; i <= HEIGH_CONSOLE / 2 + 10; i++) {
		cout << (char)219;
		GotoXY((WIDTH_CONSOLE / 2), i);
		ObstacleXlv2[idxObstaclelv2].x = WIDTH_CONSOLE / 2;
		ObstacleXlv2[idxObstaclelv2].y = i - 1;
		idxObstaclelv2++;
	}

	GotoXY((WIDTH_CONSOLE / 2), HEIGH_CONSOLE / 2 - 9);
	for (int i = HEIGH_CONSOLE / 2 - 9; i <= HEIGH_CONSOLE / 2; i++) {
		cout << (char)219;
		GotoXY((WIDTH_CONSOLE / 2), i);
		ObstacleXlv2[idxObstaclelv2].x = WIDTH_CONSOLE / 2;
		ObstacleXlv2[idxObstaclelv2].y = i;
		idxObstaclelv2++;
	}
	GotoXY((WIDTH_CONSOLE / 2), HEIGH_CONSOLE / 2);
	cout << (char)219;

}

bool checkFoodlv2(int x, int y) {
	for (int i = 0; i < idxObstaclelv2; i++) {
		if (x == ObstacleXlv2[i].x && y == ObstacleXlv2[i].y) return true;
	}
	return false;
}

void DrawMaplv3() {
	system("cls");
	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
	SetColor(15, 8);

	for (int i = HEIGH_CONSOLE / 2 - 10; i <= HEIGH_CONSOLE / 2 + 10; i++) {
		GotoXY((WIDTH_CONSOLE / 3), i);
		cout << (char)219;
		ObstacleXlv3[idxObstaclelv3].x = WIDTH_CONSOLE / 3;
		ObstacleXlv3[idxObstaclelv3].y = i;
		idxObstaclelv3++;
	}

	for (int i = HEIGH_CONSOLE / 2 - 10; i <= HEIGH_CONSOLE / 2 + 10; i++) {
		GotoXY((WIDTH_CONSOLE / 3) * 2, i);
		cout << (char)219;
		ObstacleXlv3[idxObstaclelv3].x = (WIDTH_CONSOLE / 3) * 2;
		ObstacleXlv3[idxObstaclelv3].y = i;
		idxObstaclelv3++;
	}
	SetColor(15, 4);
}

bool checkFoodlv3(int x, int y) {
	for (int i = 0; i < idxObstaclelv3; i++) {
		if (x == ObstacleXlv3[i].x && y == ObstacleXlv3[i].y) return true;
	}
	return false;
}


void DrawMaplv4() {
	system("cls");
	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
	SetColor(15, 8);
	for (int i = 0; i <= WIDTH_CONSOLE; i++) {
		GotoXY(i, 20);
		cout << (char)254;
		ObstacleXlv4[idxObstaclelv4].x = i;
		ObstacleXlv4[idxObstaclelv4].y = 20;
		idxObstaclelv4++;
	}
	for (int i = 0; i < HEIGH_CONSOLE; i++) {
		GotoXY(WIDTH_CONSOLE / 3 - 3, i);
		cout << (char)219;
		ObstacleXlv4[idxObstaclelv4].x = WIDTH_CONSOLE / 3 - 3;
		ObstacleXlv4[idxObstaclelv4].y = i;
		idxObstaclelv4++;
	}
	for (int i = 0; i < HEIGH_CONSOLE; i++) {
		GotoXY(WIDTH_CONSOLE / 3 + 35, i);
		cout << (char)219;
		ObstacleXlv4[idxObstaclelv4].x = WIDTH_CONSOLE / 3 + 35;
		ObstacleXlv4[idxObstaclelv4].y = i;
		idxObstaclelv4++;
	}
	GotoXY(0, HEIGH_CONSOLE / 2); cout << (char)204;
	GotoXY(WIDTH_CONSOLE, HEIGH_CONSOLE / 2); cout << (char)185;
	GotoXY(WIDTH_CONSOLE / 3 - 3, 0); cout << (char)203;
	GotoXY(WIDTH_CONSOLE / 3 + 35, 0); cout << (char)203;
	GotoXY(WIDTH_CONSOLE / 3 + 35, 20); cout << (char)219;
	GotoXY(WIDTH_CONSOLE / 3 - 3, 20); cout << (char)219;
	GotoXY(WIDTH_CONSOLE / 3 - 3, HEIGH_CONSOLE); cout << (char)202;
	GotoXY(WIDTH_CONSOLE / 3 + 35, HEIGH_CONSOLE); cout << (char)202;

}

bool checkFoodlv4(int x, int y) {
	for (int i = 0; i < idxObstaclelv4; i++) {
		if (x == ObstacleXlv4[i].x && y == ObstacleXlv4[i].y) return true;
	}
	return false;
}

bool CheckCollisionWithObstaclelv2() {
	for (int i = 0; i < idxObstaclelv2; ++i) {
		if (snake[SIZE_SNAKE - 1].x == ObstacleXlv2[i].x && snake[SIZE_SNAKE - 1].y == ObstacleXlv2[i].y) {
			return true;
		}
	}
	return false;
}

bool CheckCollisionWithObstaclelv3_Wall() {
	for (int i = 0; i < idxObstaclelv3; ++i) {
		if (snake[SIZE_SNAKE - 1].x == ObstacleXlv3[i].x && snake[SIZE_SNAKE - 1].y == ObstacleXlv3[i].y) {
			return true;
		}
	}
	return false;
}

bool CheckCollisionWithObstaclelv3() {
	for (int i = 0; i < SIZE_SNAKE - 1; i++) {
		if ((obstaclelv3[1].x == snake[i].x && obstaclelv3[1].y == snake[i].y) || (CheckCollisionWithObstaclelv3_Wall() == true)) return true;
	}
	return false;
}

bool CheckCollisionWithObstaclelv4() {
	for (int i = 0; i < idxObstaclelv4; ++i) {
		if (snake[SIZE_SNAKE - 1].x == ObstacleXlv4[i].x && snake[SIZE_SNAKE - 1].y == ObstacleXlv4[i].y) {
			return true;
		}
	}
	return false;
}

void ResetObstaclelv2() {
	for (int i = 0; i < idxObstaclelv2; i++) {
		ObstacleXlv2[i].x = 0;
		ObstacleXlv2[i].y = 0;
	}
}

void ResetObstaclelv3() {
	for (int i = 0; i < idxObstaclelv3; i++) {
		ObstacleXlv3[i].x = 0;
		ObstacleXlv3[i].y = 0;
	}
}

void ResetObstaclelv4() {
	for (int i = 0; i < idxObstaclelv3; i++) {
		ObstacleXlv4[i].x = 0;
		ObstacleXlv4[i].y = 0;
	}
}

void StartGame() {
	system("cls");
	ResetData(); // Intialize original data
	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE); // Draw game
	STATE = 1;//Start running Thread
	LEVEL = 1;
	SCORE = 0;
}

void StartGameLoad() {
	STATE = 1;//Start running Thread
	LEVEL = luusnake.level;
	SIZE_SNAKE = luusnake.snakeSize;
	SCORE = luusnake.luuScore;
	CHAR_LOCK = luusnake.luuCHAR_LOCK;
	MOVING = luusnake.luuMOVING;
	for (int i = 0; i < SIZE_SNAKE; i++) {
		snake[i] = luusnake.SaveSnake[i];
	}
	ChangeLevel(LEVEL);
	if (LEVEL == 3) {
		obstaclelv3[1].x = luusnake.obstacle[1].x;
		obstaclelv3[0].x = luusnake.obstacle[0].x;
		obstaclelv3[1].y = luusnake.obstacle[1].y;
		obstaclelv3[0].y = luusnake.obstacle[0].y;
	}
	FOOD_INDEX = luusnake.foodIndex;
	food[FOOD_INDEX].x = luusnake.food.x;
	food[FOOD_INDEX].y = luusnake.food.y;
}


//Function exit game
void ExitGame(HANDLE t) {
	system("cls");
	TerminateThread(t, 0);
}

//Function pause game
void PauseGame(HANDLE t) {
	SuspendThread(t);
	SetColor(11, 11);
	for (int i = 26; i < 74; i++) {
		for (int j = 3; j < 28; j++) {
			GotoXY(i, j);
			cout << (char)219;
		}
	}
	SetColor(11, 15);
	for (int i = 26; i < 74; i++) {
		GotoXY(i, 3); cout << (char)205;
		GotoXY(i, 27); cout << (char)205;
	}
	for (int i = 3; i < 28; i++) {
		GotoXY(26, i); cout << (char)186;
		GotoXY(73, i); cout << (char)186;
	}
	GotoXY(26, 3); cout << (char)201;
	GotoXY(26, 27); cout << (char)200;
	GotoXY(73, 3); cout << (char)187;
	GotoXY(73, 27); cout << (char)188;
	SetConsoleOutputCP(852);
	SetColor(11, 4);
	GotoXY(0, 7);
	printMyFile("pause.txt");
	SetColor(12, 15);
	for (int i = 33; i < 68; i++) {
		GotoXY(i, 11);
		cout << (char)205;
	}
	for (int i = 33; i < 68; i++) {
		GotoXY(i, 13);
		cout << (char)205;
	}
	GotoXY(32, 11); cout << (char)201;
	GotoXY(32, 12); cout << (char)186;
	GotoXY(32, 13); cout << (char)200;
	GotoXY(68, 11); cout << (char)187;
	GotoXY(68, 12); cout << (char)186;
	GotoXY(68, 13); cout << (char)188;
	GotoXY(33, 12); printf("             CONTINUE              ");
	SetColor(11, 4);
	for (int i = 33; i < 68; i++) {
		GotoXY(i, 15);
		cout << (char)205;
	}
	for (int i = 33; i < 68; i++) {
		GotoXY(i, 17);
		cout << (char)205;
	}
	GotoXY(32, 15); cout << (char)201;
	GotoXY(32, 16); cout << (char)186;
	GotoXY(32, 17); cout << (char)200;
	GotoXY(68, 15); cout << (char)187;
	GotoXY(68, 16); cout << (char)186;
	GotoXY(68, 17); cout << (char)188;
	GotoXY(33, 16); printf("            SAVE GAME              ");
	for (int i = 32; i < 68; i++) {
		GotoXY(i, 19);
		cout << (char)205;
	}
	for (int i = 32; i < 68; i++) {
		GotoXY(i, 21);
		cout << (char)205;
	}
	GotoXY(32, 19); cout << (char)201;
	GotoXY(32, 20); cout << (char)186;
	GotoXY(32, 21); cout << (char)200;
	GotoXY(68, 19); cout << (char)187;
	GotoXY(68, 20); cout << (char)186;
	GotoXY(68, 21); cout << (char)188;
	GotoXY(33, 20); printf("            PLAY AGAIN             ");
	for (int i = 32; i < 68; i++) {
		GotoXY(i, 23);
		cout << (char)205;
	}
	for (int i = 32; i < 68; i++) {
		GotoXY(i, 25);
		cout << (char)205;
	}
	GotoXY(32, 23); cout << (char)201;
	GotoXY(32, 24); cout << (char)186;
	GotoXY(32, 25); cout << (char)200;
	GotoXY(68, 23); cout << (char)187;
	GotoXY(68, 24); cout << (char)186;
	GotoXY(68, 25); cout << (char)188;
	GotoXY(33, 24); printf("              EXIT                 ");
	GotoXY(78, 40);
	int chon = 0;
	int toado = 15;
	do {
		char a = _getch();
		if (a == 80 || a == 's' || a == 'S' || a == '2') chon = 1;
		else if (a == 72 || a == 'w' || a == 'W' || a == '8') chon = 2;
		else if (a == 13 || a == '5') chon = 3;
		else chon = 0;
		if (chon == 1 && toado < 18) toado++;
		else if (chon == 2 && toado > 15) toado--;
		if (toado == 15)
		{
			SetColor(12, 15);
			for (int i = 33; i < 68; i++) {
				GotoXY(i, 11);
				cout << (char)205;
			}
			for (int i = 33; i < 68; i++) {
				GotoXY(i, 13);
				cout << (char)205;
			}
			GotoXY(32, 11); cout << (char)201;
			GotoXY(32, 12); cout << (char)186;
			GotoXY(32, 13); cout << (char)200;
			GotoXY(68, 11); cout << (char)187;
			GotoXY(68, 12); cout << (char)186;
			GotoXY(68, 13); cout << (char)188;
			GotoXY(33, 12); printf("             CONTINUE              ");
			SetColor(11, 4);
			for (int i = 33; i < 68; i++) {
				GotoXY(i, 15);
				cout << (char)205;
			}
			for (int i = 33; i < 68; i++) {
				GotoXY(i, 17);
				cout << (char)205;
			}
			GotoXY(32, 15); cout << (char)201;
			GotoXY(32, 16); cout << (char)186;
			GotoXY(32, 17); cout << (char)200;
			GotoXY(68, 15); cout << (char)187;
			GotoXY(68, 16); cout << (char)186;
			GotoXY(68, 17); cout << (char)188;
			GotoXY(33, 16); printf("            SAVE GAME              ");
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 19);
				cout << (char)205;
			}
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 21);
				cout << (char)205;
			}
			GotoXY(32, 19); cout << (char)201;
			GotoXY(32, 20); cout << (char)186;
			GotoXY(32, 21); cout << (char)200;
			GotoXY(68, 19); cout << (char)187;
			GotoXY(68, 20); cout << (char)186;
			GotoXY(68, 21); cout << (char)188;
			GotoXY(33, 20); printf("            PLAY AGAIN             ");
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 23);
				cout << (char)205;
			}
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 25);
				cout << (char)205;
			}
			GotoXY(32, 23); cout << (char)201;
			GotoXY(32, 24); cout << (char)186;
			GotoXY(32, 25); cout << (char)200;
			GotoXY(68, 23); cout << (char)187;
			GotoXY(68, 24); cout << (char)186;
			GotoXY(68, 25); cout << (char)188;
			GotoXY(33, 24); printf("              EXIT                 ");
			SetColor(15, 4);
			GotoXY(78, 40);
		}
		if (toado == 16)
		{
			SetColor(11, 4);
			for (int i = 33; i < 68; i++) {
				GotoXY(i, 11);
				cout << (char)205;
			}
			for (int i = 33; i < 68; i++) {
				GotoXY(i, 13);
				cout << (char)205;
			}
			GotoXY(32, 11); cout << (char)201;
			GotoXY(32, 12); cout << (char)186;
			GotoXY(32, 13); cout << (char)200;
			GotoXY(68, 11); cout << (char)187;
			GotoXY(68, 12); cout << (char)186;
			GotoXY(68, 13); cout << (char)188;
			GotoXY(33, 12); printf("             CONTINUE              ");

			SetColor(12, 15);
			for (int i = 33; i < 68; i++) {
				GotoXY(i, 15);
				cout << (char)205;
			}
			for (int i = 33; i < 68; i++) {
				GotoXY(i, 17);
				cout << (char)205;
			}
			GotoXY(32, 15); cout << (char)201;
			GotoXY(32, 16); cout << (char)186;
			GotoXY(32, 17); cout << (char)200;
			GotoXY(68, 15); cout << (char)187;
			GotoXY(68, 16); cout << (char)186;
			GotoXY(68, 17); cout << (char)188;
			GotoXY(33, 16); printf("            SAVE GAME              ");
			SetColor(11, 4);
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 19);
				cout << (char)205;
			}
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 21);
				cout << (char)205;
			}
			GotoXY(32, 19); cout << (char)201;
			GotoXY(32, 20); cout << (char)186;
			GotoXY(32, 21); cout << (char)200;
			GotoXY(68, 19); cout << (char)187;
			GotoXY(68, 20); cout << (char)186;
			GotoXY(68, 21); cout << (char)188;
			GotoXY(33, 20); printf("            PLAY AGAIN             ");
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 23);
				cout << (char)205;
			}
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 25);
				cout << (char)205;
			}
			GotoXY(32, 23); cout << (char)201;
			GotoXY(32, 24); cout << (char)186;
			GotoXY(32, 25); cout << (char)200;
			GotoXY(68, 23); cout << (char)187;
			GotoXY(68, 24); cout << (char)186;
			GotoXY(68, 25); cout << (char)188;
			GotoXY(33, 24); printf("              EXIT                 ");
			SetColor(15, 4);
			GotoXY(78, 40);
		}
		if (toado == 17)
		{
			SetColor(11, 4);
			for (int i = 33; i < 68; i++) {
				GotoXY(i, 11);
				cout << (char)205;
			}
			for (int i = 33; i < 68; i++) {
				GotoXY(i, 13);
				cout << (char)205;
			}
			GotoXY(32, 11); cout << (char)201;
			GotoXY(32, 12); cout << (char)186;
			GotoXY(32, 13); cout << (char)200;
			GotoXY(68, 11); cout << (char)187;
			GotoXY(68, 12); cout << (char)186;
			GotoXY(68, 13); cout << (char)188;
			GotoXY(33, 12); printf("             CONTINUE              ");

			for (int i = 33; i < 68; i++) {
				GotoXY(i, 15);
				cout << (char)205;
			}
			for (int i = 33; i < 68; i++) {
				GotoXY(i, 17);
				cout << (char)205;
			}
			GotoXY(32, 15); cout << (char)201;
			GotoXY(32, 16); cout << (char)186;
			GotoXY(32, 17); cout << (char)200;
			GotoXY(68, 15); cout << (char)187;
			GotoXY(68, 16); cout << (char)186;
			GotoXY(68, 17); cout << (char)188;
			GotoXY(33, 16); printf("            SAVE GAME              ");
			SetColor(12, 15);
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 19);
				cout << (char)205;
			}
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 21);
				cout << (char)205;
			}
			GotoXY(32, 19); cout << (char)201;
			GotoXY(32, 20); cout << (char)186;
			GotoXY(32, 21); cout << (char)200;
			GotoXY(68, 19); cout << (char)187;
			GotoXY(68, 20); cout << (char)186;
			GotoXY(68, 21); cout << (char)188;
			GotoXY(33, 20); printf("            PLAY AGAIN             ");
			SetColor(11, 4);
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 23);
				cout << (char)205;
			}
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 25);
				cout << (char)205;
			}
			GotoXY(32, 23); cout << (char)201;
			GotoXY(32, 24); cout << (char)186;
			GotoXY(32, 25); cout << (char)200;
			GotoXY(68, 23); cout << (char)187;
			GotoXY(68, 24); cout << (char)186;
			GotoXY(68, 25); cout << (char)188;
			GotoXY(33, 24); printf("              EXIT                 ");
			SetColor(15, 4);
			GotoXY(78, 40);
		}
		if (toado == 18)
		{
			SetColor(11, 4);
			for (int i = 33; i < 68; i++) {
				GotoXY(i, 11);
				cout << (char)205;
			}
			for (int i = 33; i < 68; i++) {
				GotoXY(i, 13);
				cout << (char)205;
			}
			GotoXY(32, 11); cout << (char)201;
			GotoXY(32, 12); cout << (char)186;
			GotoXY(32, 13); cout << (char)200;
			GotoXY(68, 11); cout << (char)187;
			GotoXY(68, 12); cout << (char)186;
			GotoXY(68, 13); cout << (char)188;
			GotoXY(33, 12); printf("             CONTINUE              ");

			for (int i = 33; i < 68; i++) {
				GotoXY(i, 15);
				cout << (char)205;
			}
			for (int i = 33; i < 68; i++) {
				GotoXY(i, 17);
				cout << (char)205;
			}
			GotoXY(32, 15); cout << (char)201;
			GotoXY(32, 16); cout << (char)186;
			GotoXY(32, 17); cout << (char)200;
			GotoXY(68, 15); cout << (char)187;
			GotoXY(68, 16); cout << (char)186;
			GotoXY(68, 17); cout << (char)188;
			GotoXY(33, 16); printf("            SAVE GAME              ");

			for (int i = 32; i < 68; i++) {
				GotoXY(i, 19);
				cout << (char)205;
			}
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 21);
				cout << (char)205;
			}
			GotoXY(32, 19); cout << (char)201;
			GotoXY(32, 20); cout << (char)186;
			GotoXY(32, 21); cout << (char)200;
			GotoXY(68, 19); cout << (char)187;
			GotoXY(68, 20); cout << (char)186;
			GotoXY(68, 21); cout << (char)188;
			GotoXY(33, 20); printf("            PLAY AGAIN             ");

			SetColor(12, 15);
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 23);
				cout << (char)205;
			}
			for (int i = 32; i < 68; i++) {
				GotoXY(i, 25);
				cout << (char)205;
			}
			GotoXY(32, 23); cout << (char)201;
			GotoXY(32, 24); cout << (char)186;
			GotoXY(32, 25); cout << (char)200;
			GotoXY(68, 23); cout << (char)187;
			GotoXY(68, 24); cout << (char)186;
			GotoXY(68, 25); cout << (char)188;
			GotoXY(33, 24); printf("              EXIT                 ");
			SetColor(15, 4);
			GotoXY(78, 40);
		}
	} while (chon != 3);
	if (toado == 15) {
		system("cls");
		if (LEVEL == 1) {
			DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
		}
		else if (LEVEL == 2) {
			DrawMaplv2();
		}
		else if (LEVEL == 3) {
			DrawMaplv3();
		}
		else if (LEVEL == 4) {
			DrawMaplv4();
		}
		
		ResumeThread(t);
	}
	else if (toado == 16) {
		
		system("cls");
		SetColor(15, 4);
		for (int i = 66; i < 100; i++) {
			GotoXY(i, 16);
			cout << (char)205;
			GotoXY(i, 23);
			cout << (char)205;
		}
		for (int i = 16; i < 24; i++) {
			GotoXY(65, i);
			cout << (char)186;
			GotoXY(100, i);
			cout << (char)186;
		}
		GotoXY(65, 16); cout << (char)201;
		GotoXY(65, 23); cout << (char)200;
		GotoXY(100, 16); cout << (char)187;
		GotoXY(100, 23); cout << (char)188;
		SetColor(15, 0);
		char testTemp[20];
		GotoXY(72, 18);
		cout << "Input your name file: \n";
		GotoXY(78, 20);
		cin.getline(testTemp, 21);
		do {
			if (checkName(saveName, testTemp)) {
				GotoXY(68, 18);
				cout << "Input your name file again: \n";
				GotoXY(78, 20);
				cout << "                ";
				GotoXY(78, 20);
				cin.getline(testTemp, 21);
			}
		} while (checkName(saveName, testTemp));
		saveName.size++;
		saveName.name[saveName.size - 1] = testTemp;
		writeFileName(saveName, (char*)nameFile);
		ghifile(luusnake, testTemp);
		system("cls");
		menuGame();
	}
	else if (toado == 17) {
		system("cls");
		playGame(-1);
	}
	else if (toado == 18)
	{
		system("cls");
		menuGame();

	}
}



void DrawPortal() {
	SetColor(15, 9);
	GotoXY(100, 18);
	cout << (char)175;
	GotoXY(101, 17); cout << (char)187;
	GotoXY(101, 19); cout << (char)188;
	GotoXY(100, 17); cout << (char)204;
	GotoXY(100, 19); cout << (char)204;
	SetColor(15, 4);
	GotoXY(0, 0); cout << (char)201;
	GotoXY(103, 0);
}

void DrawSnakeAndFood(const char* str) {
	for (int i = 0; i < SIZE_SNAKE; i++) {
		GotoXY(snake[i].x, snake[i].y);
		cout << str;
	}
	GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
	cout << str;
}
//LEVEL 3

void DrawObstaclelv3(const char* str) {
	for (int i = 0; i < 2; i++) {
		GotoXY(obstaclelv3[i].x, obstaclelv3[i].y);
		cout << str;
	}
}


void ChangeLevel(int level) {
	for (int i = 116; i < 139; i++) {
		for (int j = 20; j < 35; j++) {
			GotoXY(i, j); cout << ' ';
		}
	}
	switch (level) {
	case 1:
		ResetObstaclelv2();
		ResetObstaclelv3();
		ResetObstaclelv4();
		FOOD_INDEX = 0;
		GenerateFood();
		break;
	case 2:
		ResetObstaclelv3();
		ResetObstaclelv4();
		FOOD_INDEX = 0;
		DrawMaplv2();
		for (int i = SIZE_SNAKE - 1; i >= 0; i--) {
			snake[i].x = i + 3;
			snake[i].y = 4;
		}
		GenerateFood();
		SPEED += 0.1;
		break;
	case 3:
		ResetObstaclelv2();
		ResetObstaclelv4();
		FOOD_INDEX = 0;
		GenerateFood();
		DrawMaplv3();
		for (int i = SIZE_SNAKE - 1; i >= 0; i--) {
			snake[i].x = i + 3;
			snake[i].y = 4;
		}
		SPEED += 0.1;
		break;
	case 4:
		ResetObstaclelv2();
		ResetObstaclelv3();
		FOOD_INDEX = 0;
		GenerateFood();
		DrawMaplv4();
		for (int i = SIZE_SNAKE - 1; i >= 0; i--) {
			snake[i].x = i + 3;
			snake[i].y = 4;
		}
		SPEED += 0.1;

	}
}




void Eat() {
	PlayEatSound();
	snake[SIZE_SNAKE] = food[FOOD_INDEX];
	FOOD_INDEX++;
	SIZE_SNAKE++;

}

//Function to process the dead of snake
void ProcessDead() {
	if (SIZE_SNAKE == MAX_SIZE_SNAKE) {
		STATE = 0;
		PlayWinSound();
		SetColor(15, 12);
		GotoXY(0, 9);
		printMyFile("victory.txt");
	}
	else {
		STATE = 0;
		PlayDeadSound();
		BlinkSnake(5, 300);
		SetConsoleOutputCP(852);
		SetColor(15, 12);
		GotoXY(0, 2);
		printMyFile("gameover.txt");
		SetColor(15, 0);
		SetColor(15, 4);
	}
}

void DrawSnakeAndFood1() {
	char str;
	int idx = 0;
	char a[] = { '2','3','1','2','0','2','2','8','2','3','1','2','0','2','2','0','2','3','1','2','0','2' ,'1','8','2','3','1','2','0','2' ,'1','6','2','3','1','2','0','2' ,'3','8' };

	
	for (int i = 0; i < SIZE_SNAKE; i++) {
		str = a[i];
		SetColor(5, 15);
		GotoXY(snake[i].x, snake[i].y);
		cout << str;
		SetColor(15, 4);
	}
	if (FOOD_INDEX < MAX_SIZE_FOOD) {
		GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
		cout << (char)3;
	}
	else {

		GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
		str = a[idx + 1];
		cout << (char)201;
	}
}

bool CheckCollision() {
	for (int i = 1; i < SIZE_SNAKE - 1; i++) {
		if (snake[SIZE_SNAKE - 1].x == snake[i].x && snake[SIZE_SNAKE - 1].y == snake[i].y) return true;
	}
	return false;
}

void MoveRight() {
	if ((FOOD_INDEX != MAX_SIZE_FOOD) && snake[SIZE_SNAKE - 1].x + 1 == WIDTH_CONSOLE) {
		ProcessDead();
	}
	else if ((FOOD_INDEX == MAX_SIZE_FOOD) && (snake[SIZE_SNAKE - 1].x + 1 == WIDTH_CONSOLE) && (snake[SIZE_SNAKE - 1].y != 18)) {
		ProcessDead();
	}

	else {
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
			Eat();

		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].x++;
	}
}
void MoveLeft() {
	if (snake[SIZE_SNAKE - 1].x - 1 == 0) {
		ProcessDead();
	}
	else {
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
			Eat();

		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].x--;
	}
}

void MoveDown() {
	if (snake[SIZE_SNAKE - 1].y + 1 == HEIGH_CONSOLE) {
		ProcessDead();
	}
	else {
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
			Eat();

		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].y++;
	}
}

void MoveUp() {
	if (snake[SIZE_SNAKE - 1].y - 1 == 0) {
		ProcessDead();
	}
	else {
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
			Eat();

		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].y--;
	}
}

bool GameOver() {
	if (CheckCollision() == true) return true;
	if (LEVEL == 2) {
		if (CheckCollisionWithObstaclelv2() == true) return true;
	}
	else if (LEVEL == 3) {
		if (CheckCollisionWithObstaclelv3() == true) return true;
	}
	else if (LEVEL == 4) {
		if (CheckCollisionWithObstaclelv4() == true) return true;
	}
	return false;
}

void Move1() {
	for (int i = 0; i < 1; i++) {
		obstaclelv3[i].x = obstaclelv3[i + 1].x;
		obstaclelv3[i].y = obstaclelv3[i + 1].y;
	}
	obstaclelv3[1].x++;
	obstaclelv3[1].y++;
}
void Move2() {
	for (int i = 0; i < 1; i++) {
		obstaclelv3[i].x = obstaclelv3[i + 1].x;
		obstaclelv3[i].y = obstaclelv3[i + 1].y;
	}
	obstaclelv3[1].x++;
	obstaclelv3[1].y--;
}
void Move3() {
	for (int i = 0; i < 1; i++) {
		obstaclelv3[i].x = obstaclelv3[i + 1].x;
		obstaclelv3[i].y = obstaclelv3[i + 1].y;
	}
	obstaclelv3[1].x--;
	obstaclelv3[1].y--;
}
void Move4() {
	for (int i = 0; i < 1; i++) {
		obstaclelv3[i].x = obstaclelv3[i + 1].x;
		obstaclelv3[i].y = obstaclelv3[i + 1].y;
	}
	obstaclelv3[1].x--;
	obstaclelv3[1].y++;
}
void settingObstacle() {
	MovingObstacle = 1;
	obstaclelv3[0] = { 30,20 };
	obstaclelv3[1] = { 31,20 };
}

void setThread() {
	for (int i = 0; i <= HEIGH_CONSOLE; i++) {
		GotoXY(103, i);
		cout << (char)219;
		GotoXY(150, i);
		cout << (char)219;
	}
	for (int i = 104; i < 150; i++) {
		GotoXY(i, 0);
		cout << (char)223;
		GotoXY(i, 5);
		cout << (char)42;
		GotoXY(i, HEIGH_CONSOLE);
		cout << (char)220;
	}
	SetColor(15, 0);
	GotoXY(112, 7);
	SCORE = SIZE_SNAKE * 100;
	cout << "SCORE:             ";
	SetColor(15, 10);
	cout << SIZE_SNAKE * 100;
	SetColor(15, 0);
	GotoXY(112, 8);
	cout << "SPEED:             ";
	SetColor(15, 10);
	cout << "x" << SPEED;
	SetColor(15, 0);
	GotoXY(112, 9);
	cout << "FOOD_INDEX:        ";
	SetColor(15, 10);

	cout << FOOD_INDEX;
	GotoXY(112, 11); cout << "Press 'P' to PAUSE";
	GotoXY(112, 12); cout << "Press 'L' to SAVE";
	GotoXY(112, 13); cout << "Press 'ESC' to EXIT";
	GotoXY(112, 14); cout << "Press 'Y' to PLAY AGAIN";
	GotoXY(112, 15); cout << "Press 'B' to BACK MENU";

	SetColor(15, 0);
	for (int i = 20; i < 36; i++) {
		GotoXY(115, i);
		cout << (char)219;
		GotoXY(139, i);
		cout << (char)219;
	}
	for (int i = 115; i < 140; i++) {
		GotoXY(i, 36);
		cout << (char)223;
	}
	for (int i = 115; i < 123; i++) {
		GotoXY(i, 19);
		cout << (char)220;
	}
	for (int i = 132; i < 140; i++) {
		GotoXY(i, 19);
		cout << (char)220;
	}
	for (int i = 123; i < 132; i++) {
		GotoXY(i, 19); cout << (char)219;
	}

	for (int i = 120; i <= 122; i++) {
		SetColor(15, 0);
		GotoXY(i, 35); cout << (char)177;
	}

	//

	for (int i = 121; i <= 123; i++) {
		SetColor(15, 0);
		GotoXY(i, 34); cout << (char)177;
	}

	//

	for (int i = 122; i <= 124; i++) {
		SetColor(15, 0);
		GotoXY(i, 33); cout << (char)177;
	}

	//

	for (int i = 123; i <= 126; i++) {
		SetColor(15, 0);
		GotoXY(i, 32); cout << (char)177;
	}

	/////////

	for (int i = 123; i <= 127; i++) {
		SetColor(15, 0);
		GotoXY(i, 31); cout << (char)177;
	}
	//
	for (int i = 124; i <= 129; i++) {
		SetColor(15, 0);
		GotoXY(i, 30); cout << (char)177;
	}
	//
	for (int i = 124; i <= 130; i++) {
		SetColor(15, 0);
		GotoXY(i, 29); cout << (char)177;
	}
	//
	for (int i = 125; i <= 131; i++) {
		SetColor(15, 0);
		GotoXY(i, 28); cout << (char)177;
	}
	/////////
	for (int i = 121; i <= 132; i++) {
		SetColor(15, 0);
		GotoXY(i, 27); cout << (char)177;
	}
	//
	
	for (int i = 121; i <= 134; i++) {
		SetColor(15, 0);
		GotoXY(i, 26); cout << (char)177;
	}
	
	//
	
	for (int i = 122; i <= 129; i++) {
		SetColor(15, 0);
		GotoXY(i, 25); cout << (char)177;
	}
	
	//
	
	for (int i = 123; i <= 130; i++) {
		SetColor(15, 0);
		GotoXY(i, 24); cout << (char)177;
	}
	
	//////////////////
	
	for (int i = 123; i <= 131; i++) {
		SetColor(15, 0);
		GotoXY(i, 23); cout << (char)177;
	}	
	//
	for (int i = 124; i <= 132; i++) {
		SetColor(15, 0);
		GotoXY(i, 22); cout << (char)177;
	}
	//
	
	for (int i = 125; i <= 133; i++) {
		SetColor(15, 0);
		GotoXY(i, 21); cout << (char)177;
	}
	
	//
	
	for (int i = 125; i <= 134; i++) {
		SetColor(15, 0);
		GotoXY(i, 20); cout << (char)177;
	}
	

	if (FOOD_INDEX == 1) {
		for (int i = 116; i <= 119; i++) {
			SetColor(15, 10);
			GotoXY(i, 35); cout << (char)219;
		}
		for (int i = 120; i <= 122; i++) {
			SetColor(15, 6);
			GotoXY(i, 35); cout << (char)177;
		}
		for (int i = 123; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 35); cout << (char)219;
		}
		//
		for (int i = 116; i <= 120; i++) {
			SetColor(15, 10);
			GotoXY(i, 34); cout << (char)219;
		}
		for (int i = 121; i <= 123; i++) {
			SetColor(15, 6);
			GotoXY(i, 34); cout << (char)177;
		}
		for (int i = 124; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 34); cout << (char)219;
		}
		//
		for (int i = 116; i <= 121; i++) {
			SetColor(15, 10);
			GotoXY(i, 33); cout << (char)219;
		}
		for (int i = 122; i <= 124; i++) {
			SetColor(15, 6);
			GotoXY(i, 33); cout << (char)177;
		}
		for (int i = 125; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 33); cout << (char)219;
		}
		//
		for (int i = 116; i <= 122; i++) {
			SetColor(15, 10);
			GotoXY(i, 32); cout << (char)219;
		}
		for (int i = 123; i <= 126; i++) {
			SetColor(15, 6);
			GotoXY(i, 32); cout << (char)177;
		}
		for (int i = 127; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 32); cout << (char)219;
		}
	}
	else if (FOOD_INDEX == 2) {
		for (int i = 116; i <= 119; i++) {
			SetColor(15, 10);
			GotoXY(i, 35); cout << (char)219;
		}
		for (int i = 120; i <= 122; i++) {
			SetColor(15, 6);
			GotoXY(i, 35); cout << (char)177;
		}
		for (int i = 123; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 35); cout << (char)219;
		}
		//
		for (int i = 116; i <= 120; i++) {
			SetColor(15, 10);
			GotoXY(i, 34); cout << (char)219;
		}
		for (int i = 121; i <= 123; i++) {
			SetColor(15, 6);
			GotoXY(i, 34); cout << (char)177;
		}
		for (int i = 124; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 34); cout << (char)219;
		}
		//
		for (int i = 116; i <= 121; i++) {
			SetColor(15, 10);
			GotoXY(i, 33); cout << (char)219;
		}
		for (int i = 122; i <= 124; i++) {
			SetColor(15, 6);
			GotoXY(i, 33); cout << (char)177;
		}
		for (int i = 125; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 33); cout << (char)219;
		}
		//
		for (int i = 116; i <= 122; i++) {
			SetColor(15, 10);
			GotoXY(i, 32); cout << (char)219;
		}
		for (int i = 123; i <= 126; i++) {
			SetColor(15, 6);
			GotoXY(i, 32); cout << (char)177;
		}
		for (int i = 127; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 32); cout << (char)219;
		}
		/////////
		for (int i = 116; i <= 122; i++) {
			SetColor(15, 10);
			GotoXY(i, 31); cout << (char)219;
		}
		for (int i = 123; i <= 127; i++) {
			SetColor(15, 6);
			GotoXY(i, 31); cout << (char)177;
		}
		for (int i = 128; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 31); cout << (char)219;
		}
		//
		for (int i = 116; i <= 123; i++) {
			SetColor(15, 10);
			GotoXY(i, 30); cout << (char)219;
		}
		for (int i = 124; i <= 129; i++) {
			SetColor(15, 6);
			GotoXY(i, 30); cout << (char)177;
		}
		for (int i = 130; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 30); cout << (char)219;
		}
		//
		for (int i = 116; i <= 123; i++) {
			SetColor(15, 10);
			GotoXY(i, 29); cout << (char)219;
		}
		for (int i = 124; i <= 130; i++) {
			SetColor(15, 6);
			GotoXY(i, 29); cout << (char)177;
		}
		for (int i = 131; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 29); cout << (char)219;
		}
		//
		for (int i = 116; i <= 124; i++) {
			SetColor(15, 10);
			GotoXY(i, 28); cout << (char)219;
		}
		for (int i = 125; i <= 131; i++) {
			SetColor(15, 6);
			GotoXY(i, 28); cout << (char)177;
		}
		for (int i = 132; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 28); cout << (char)219;
		}
	}
	else if (FOOD_INDEX == 3) {
		for (int i = 116; i <= 119; i++) {
			SetColor(15, 10);
			GotoXY(i, 35); cout << (char)219;
		}
		for (int i = 120; i <= 122; i++) {
			SetColor(15, 6);
			GotoXY(i, 35); cout << (char)177;
		}
		for (int i = 123; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 35); cout << (char)219;
		}
		//
		for (int i = 116; i <= 120; i++) {
			SetColor(15, 10);
			GotoXY(i, 34); cout << (char)219;
		}
		for (int i = 121; i <= 123; i++) {
			SetColor(15, 6);
			GotoXY(i, 34); cout << (char)177;
		}
		for (int i = 124; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 34); cout << (char)219;
		}
		//
		for (int i = 116; i <= 121; i++) {
			SetColor(15, 10);
			GotoXY(i, 33); cout << (char)219;
		}
		for (int i = 122; i <= 124; i++) {
			SetColor(15, 6);
			GotoXY(i, 33); cout << (char)177;
		}
		for (int i = 125; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 33); cout << (char)219;
		}
		//
		for (int i = 116; i <= 122; i++) {
			SetColor(15, 10);
			GotoXY(i, 32); cout << (char)219;
		}
		for (int i = 123; i <= 126; i++) {
			SetColor(15, 6);
			GotoXY(i, 32); cout << (char)177;
		}
		for (int i = 127; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 32); cout << (char)219;
		}
		/////////
		for (int i = 116; i <= 122; i++) {
			SetColor(15, 10);
			GotoXY(i, 31); cout << (char)219;
		}
		for (int i = 123; i <= 127; i++) {
			SetColor(15, 6);
			GotoXY(i, 31); cout << (char)177;
		}
		for (int i = 128; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 31); cout << (char)219;
		}
		//
		for (int i = 116; i <= 123; i++) {
			SetColor(15, 10);
			GotoXY(i, 30); cout << (char)219;
		}
		for (int i = 124; i <= 129; i++) {
			SetColor(15, 6);
			GotoXY(i, 30); cout << (char)177;
		}
		for (int i = 130; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 30); cout << (char)219;
		}
		//
		for (int i = 116; i <= 123; i++) {
			SetColor(15, 10);
			GotoXY(i, 29); cout << (char)219;
		}
		for (int i = 124; i <= 130; i++) {
			SetColor(15, 6);
			GotoXY(i, 29); cout << (char)177;
		}
		for (int i = 131; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 29); cout << (char)219;
		}
		//
		for (int i = 116; i <= 124; i++) {
			SetColor(15, 10);
			GotoXY(i, 28); cout << (char)219;
		}
		for (int i = 125; i <= 131; i++) {
			SetColor(15, 6);
			GotoXY(i, 28); cout << (char)177;
		}
		for (int i = 132; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 28); cout << (char)219;
		}
		/////////
		for (int i = 116; i <= 120; i++) {
			SetColor(15, 10);
			GotoXY(i, 27); cout << (char)219;
		}
		for (int i = 121; i <= 132; i++) {
			SetColor(15, 6);
			GotoXY(i, 27); cout << (char)177;
		}
		for (int i = 133; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 27); cout << (char)219;
		}
		//
		for (int i = 116; i <= 120; i++) {
			SetColor(15, 10);
			GotoXY(i, 26); cout << (char)219;
		}
		for (int i = 121; i <= 134; i++) {
			SetColor(15, 6);
			GotoXY(i, 26); cout << (char)177;
		}
		for (int i = 135; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 26); cout << (char)219;
		}
		//
		for (int i = 116; i <= 121; i++) {
			SetColor(15, 10);
			GotoXY(i, 25); cout << (char)219;
		}
		for (int i = 122; i <= 129; i++) {
			SetColor(15, 6);
			GotoXY(i, 25); cout << (char)177;
		}
		for (int i = 130; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 25); cout << (char)219;
		}
		//
		for (int i = 116; i <= 122; i++) {
			SetColor(15, 10);
			GotoXY(i, 24); cout << (char)219;
		}
		for (int i = 123; i <= 130; i++) {
			SetColor(15, 6);
			GotoXY(i, 24); cout << (char)177;
		}
		for (int i = 131; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 24); cout << (char)219;
		}
	}
	else if (FOOD_INDEX == 4) {
		for (int i = 116; i <= 119; i++) {
			SetColor(15, 10);
			GotoXY(i, 35); cout << (char)219;
		}
		for (int i = 120; i <= 122; i++) {
			SetColor(15, 6);
			GotoXY(i, 35); cout << (char)177;
		}
		for (int i = 123; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 35); cout << (char)219;
		}
		//
		for (int i = 116; i <= 120; i++) {
			SetColor(15, 10);
			GotoXY(i, 34); cout << (char)219;
		}
		for (int i = 121; i <= 123; i++) {
			SetColor(15, 6);
			GotoXY(i, 34); cout << (char)177;
		}
		for (int i = 124; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 34); cout << (char)219;
		}
		//
		for (int i = 116; i <= 121; i++) {
			SetColor(15, 10);
			GotoXY(i, 33); cout << (char)219;
		}
		for (int i = 122; i <= 124; i++) {
			SetColor(15, 6);
			GotoXY(i, 33); cout << (char)177;
		}
		for (int i = 125; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 33); cout << (char)219;
		}
		//
		for (int i = 116; i <= 122; i++) {
			SetColor(15, 10);
			GotoXY(i, 32); cout << (char)219;
		}
		for (int i = 123; i <= 126; i++) {
			SetColor(15, 6);
			GotoXY(i, 32); cout << (char)177;
		}
		for (int i = 127; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 32); cout << (char)219;
		}
		/////////
		for (int i = 116; i <= 122; i++) {
			SetColor(15, 10);
			GotoXY(i, 31); cout << (char)219;
		}
		for (int i = 123; i <= 127; i++) {
			SetColor(15, 6);
			GotoXY(i, 31); cout << (char)177;
		}
		for (int i = 128; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 31); cout << (char)219;
		}
		//
		for (int i = 116; i <= 123; i++) {
			SetColor(15, 10);
			GotoXY(i, 30); cout << (char)219;
		}
		for (int i = 124; i <= 129; i++) {
			SetColor(15, 6);
			GotoXY(i, 30); cout << (char)177;
		}
		for (int i = 130; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 30); cout << (char)219;
		}
		//
		for (int i = 116; i <= 123; i++) {
			SetColor(15, 10);
			GotoXY(i, 29); cout << (char)219;
		}
		for (int i = 124; i <= 130; i++) {
			SetColor(15, 6);
			GotoXY(i, 29); cout << (char)177;
		}
		for (int i = 131; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 29); cout << (char)219;
		}
		//
		for (int i = 116; i <= 124; i++) {
			SetColor(15, 10);
			GotoXY(i, 28); cout << (char)219;
		}
		for (int i = 125; i <= 131; i++) {
			SetColor(15, 6);
			GotoXY(i, 28); cout << (char)177;
		}
		for (int i = 132; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 28); cout << (char)219;
		}
		/////////
		for (int i = 116; i <= 120; i++) {
			SetColor(15, 10);
			GotoXY(i, 27); cout << (char)219;
		}
		for (int i = 121; i <= 132; i++) {
			SetColor(15, 6);
			GotoXY(i, 27); cout << (char)177;
		}
		for (int i = 133; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 27); cout << (char)219;
		}
		//
		for (int i = 116; i <= 120; i++) {
			SetColor(15, 10);
			GotoXY(i, 26); cout << (char)219;
		}
		for (int i = 121; i <= 134; i++) {
			SetColor(15, 6);
			GotoXY(i, 26); cout << (char)177;
		}
		for (int i = 135; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 26); cout << (char)219;
		}
		//
		for (int i = 116; i <= 121; i++) {
			SetColor(15, 10);
			GotoXY(i, 25); cout << (char)219;
		}
		for (int i = 122; i <= 129; i++) {
			SetColor(15, 6);
			GotoXY(i, 25); cout << (char)177;
		}
		for (int i = 130; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 25); cout << (char)219;
		}
		//
		for (int i = 116; i <= 122; i++) {
			SetColor(15, 10);
			GotoXY(i, 24); cout << (char)219;
		}
		for (int i = 123; i <= 130; i++) {
			SetColor(15, 6);
			GotoXY(i, 24); cout << (char)177;
		}
		for (int i = 131; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 24); cout << (char)219;
		}
		//////////////////
		for (int i = 116; i <= 122; i++) {
			SetColor(15, 10);
			GotoXY(i, 23); cout << (char)219;
		}
		for (int i = 123; i <= 131; i++) {
			SetColor(15, 6);
			GotoXY(i, 23); cout << (char)177;
		}
		for (int i = 132; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 23); cout << (char)219;
		}
		//
		for (int i = 116; i <= 123; i++) {
			SetColor(15, 10);
			GotoXY(i, 22); cout << (char)219;
		}
		for (int i = 124; i <= 132; i++) {
			SetColor(15, 6);
			GotoXY(i, 22); cout << (char)177;
		}
		for (int i = 133; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 22); cout << (char)219;
		}
		//
		for (int i = 116; i <= 124; i++) {
			SetColor(15, 10);
			GotoXY(i, 21); cout << (char)219;
		}
		for (int i = 125; i <= 133; i++) {
			SetColor(15, 6);
			GotoXY(i, 21); cout << (char)177;
		}
		for (int i = 134; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 21); cout << (char)219;
		}
		//
		for (int i = 116; i <= 124; i++) {
			SetColor(15, 10);
			GotoXY(i, 20); cout << (char)219;
		}
		for (int i = 125; i <= 134; i++) {
			SetColor(15, 6);
			GotoXY(i, 20); cout << (char)177;
		}
		for (int i = 135; i <= 138; i++) {
			SetColor(15, 10);
			GotoXY(i, 20); cout << (char)219;
		}
	}

	if (LEVEL == 1) {
		SetConsoleOutputCP(852);
		SetColor(15, 10);
		GotoXY(0, 2);
		printMyFile("level1.txt");
		SetColor(15, 4);
	}
	if (LEVEL == 2) {
		SetConsoleOutputCP(852);
		SetColor(15, 10);
		GotoXY(0, 2);
		printMyFile("level2.txt");
		SetColor(15, 4);
	}
	if (LEVEL == 3) {
		SetConsoleOutputCP(852);
		SetColor(15, 10);
		GotoXY(0, 2);
		printMyFile("level3.txt");
		SetColor(15, 4);
	}
	if (LEVEL == 4) {
		SetConsoleOutputCP(852);
		SetColor(15, 10);
		GotoXY(0, 2);
		printMyFile("level4.txt");
		SetColor(15, 4);
	}
}

void ThreadFunc() {
	while (1) {
		if (STATE == 1) {//If my snake is alive
			DrawSnakeAndFood(" ");
			switch (MOVING) {
			case 'A':
				MoveLeft();
				break;
			case 'D':
				MoveRight();
				break;
			case 'W':
				MoveUp();
				break;
			case 'S':
				MoveDown();
				break;
			}
			DrawSnakeAndFood1();

			if (LEVEL == 3) {
				DrawObstaclelv3(" ");
				switch (MovingObstacle) {
				case 1:
					Move1();
					break;
				case 2:
					Move2();
					break;
				case 3:
					Move3();
					break;
				case 4:
					Move4();
					break;
				}
				DrawObstaclelv3("#");
				if ((obstaclelv3[1].y + 1 == HEIGH_CONSOLE) && MovingObstacle == 1) MovingObstacle = 2;
				else if ((obstaclelv3[1].y + 1 == HEIGH_CONSOLE) && MovingObstacle == 4) MovingObstacle = 3;
				else if ((obstaclelv3[1].y - 1 == 0) && MovingObstacle == 2) MovingObstacle = 1;
				else if ((obstaclelv3[1].y - 1 == 0) && MovingObstacle == 3) MovingObstacle = 4;
				else if ((obstaclelv3[1].x + 1 == WIDTH_CONSOLE) && MovingObstacle == 1) MovingObstacle = 4;
				else if ((obstaclelv3[1].x + 1 == WIDTH_CONSOLE) && MovingObstacle == 2) MovingObstacle = 3;
				else if ((obstaclelv3[1].x - 1 == 0) && MovingObstacle == 3) MovingObstacle = 2;
				else if ((obstaclelv3[1].x - 1 == 0) && MovingObstacle == 4) MovingObstacle = 1;
				else if ((obstaclelv3[1].x + 1 == (WIDTH_CONSOLE / 3)) && (obstaclelv3[1].y + 1 >= HEIGH_CONSOLE / 2 - 10 && obstaclelv3[1].y + 1 <= HEIGH_CONSOLE / 2 + 10) && MovingObstacle == 2) MovingObstacle = 3;
				else if ((obstaclelv3[1].x + 1 == (WIDTH_CONSOLE / 3)) && (obstaclelv3[1].y + 1 >= HEIGH_CONSOLE / 2 - 10 && obstaclelv3[1].y + 1 <= HEIGH_CONSOLE / 2 + 10) && MovingObstacle == 1) MovingObstacle = 4;
				else if ((obstaclelv3[1].x - 1 == (WIDTH_CONSOLE / 3)) && (obstaclelv3[1].y + 1 >= HEIGH_CONSOLE / 2 - 10 && obstaclelv3[1].y + 1 <= HEIGH_CONSOLE / 2 + 10) && MovingObstacle == 3) MovingObstacle = 2;
				else if ((obstaclelv3[1].x - 1 == (WIDTH_CONSOLE / 3)) && (obstaclelv3[1].y + 1 >= HEIGH_CONSOLE / 2 - 10 && obstaclelv3[1].y + 1 <= HEIGH_CONSOLE / 2 + 10) && MovingObstacle == 4) MovingObstacle = 1;
				else if ((obstaclelv3[1].x + 1 == (WIDTH_CONSOLE / 3) * 2) && (obstaclelv3[1].y + 1 >= HEIGH_CONSOLE / 2 - 10 && obstaclelv3[1].y + 1 <= HEIGH_CONSOLE / 2 + 10) && MovingObstacle == 2) MovingObstacle = 3;
				else if ((obstaclelv3[1].x + 1 == (WIDTH_CONSOLE / 3) * 2) && (obstaclelv3[1].y + 1 >= HEIGH_CONSOLE / 2 - 10 && obstaclelv3[1].y + 1 <= HEIGH_CONSOLE / 2 + 10) && MovingObstacle == 1) MovingObstacle = 4;
				else if ((obstaclelv3[1].x - 1 == (WIDTH_CONSOLE / 3) * 2) && (obstaclelv3[1].y + 1 >= HEIGH_CONSOLE / 2 - 10 && obstaclelv3[1].y + 1 <= HEIGH_CONSOLE / 2 + 10) && MovingObstacle == 3) MovingObstacle = 2;
				else if ((obstaclelv3[1].x - 1 == (WIDTH_CONSOLE / 3) * 2) && (obstaclelv3[1].y + 1 >= HEIGH_CONSOLE / 2 - 10 && obstaclelv3[1].y + 1 <= HEIGH_CONSOLE / 2 + 10) && MovingObstacle == 4) MovingObstacle = 1;
			}
			else if (LEVEL == 4) {

				SetColor(15, 1);
				GotoXY(15, 8);
				cout << char(21);
				GotoXY(85, 25);
				cout << (char)21;

				SetColor(15, 2);
				GotoXY(78, 33);
				cout << (char)21;
				GotoXY(15, 34);
				cout << (char)21;

				SetColor(15, 6);
				GotoXY(20, 27);
				cout << (char)21;
				GotoXY(90, 4);
				cout << (char)21;

				SetColor(15, 0);
				GotoXY(80, 17);
				cout << (char)21;
				GotoXY(50, 4);
				cout << (char)21;

				SetColor(15, 13);
				GotoXY(44, 13);
				cout << (char)21;
				GotoXY(44, 28);
				cout << (char)21;

				SetColor(15, 4);


				if ((snake[SIZE_SNAKE - 1].x == 15 && snake[SIZE_SNAKE - 1].y == 8)) {
					snake[SIZE_SNAKE - 1].x = 85;
					snake[SIZE_SNAKE - 1].y = 25;
				}
				else if ((snake[SIZE_SNAKE - 1].x == 85 && snake[SIZE_SNAKE - 1].y == 25)) {
					snake[SIZE_SNAKE - 1].x = 15;
					snake[SIZE_SNAKE - 1].y = 8;
				}


				else if ((snake[SIZE_SNAKE - 1].x == 78 && snake[SIZE_SNAKE - 1].y == 33)) {
					snake[SIZE_SNAKE - 1].x = 15;
					snake[SIZE_SNAKE - 1].y = 34;
				}
				else if ((snake[SIZE_SNAKE - 1].x == 15 && snake[SIZE_SNAKE - 1].y == 34)) {
					snake[SIZE_SNAKE - 1].x = 78;
					snake[SIZE_SNAKE - 1].y = 33;
				}


				else if ((snake[SIZE_SNAKE - 1].x == 20 && snake[SIZE_SNAKE - 1].y == 27)) {
					snake[SIZE_SNAKE - 1].x = 90;
					snake[SIZE_SNAKE - 1].y = 4;
				}
				else if ((snake[SIZE_SNAKE - 1].x == 90 && snake[SIZE_SNAKE - 1].y == 4)) {
					snake[SIZE_SNAKE - 1].x = 20;
					snake[SIZE_SNAKE - 1].y = 27;
				}


				else if ((snake[SIZE_SNAKE - 1].x == 80 && snake[SIZE_SNAKE - 1].y == 17)) {
					snake[SIZE_SNAKE - 1].x = 50;
					snake[SIZE_SNAKE - 1].y = 4;
				}
				else if ((snake[SIZE_SNAKE - 1].x == 50 && snake[SIZE_SNAKE - 1].y == 4)) {
					snake[SIZE_SNAKE - 1].x = 80;
					snake[SIZE_SNAKE - 1].y = 17;
				}


				else if ((snake[SIZE_SNAKE - 1].x == 44 && snake[SIZE_SNAKE - 1].y == 13)) {
					snake[SIZE_SNAKE - 1].x = 44;
					snake[SIZE_SNAKE - 1].y = 28;
				}
				else if ((snake[SIZE_SNAKE - 1].x == 44 && snake[SIZE_SNAKE - 1].y == 28)) {
					snake[SIZE_SNAKE - 1].x = 44;
					snake[SIZE_SNAKE - 1].y = 13;
				}

			}

			setThread();
			
			if (GameOver() == true) {
				ProcessDead();
				SCORE = 0;
			}
			if (FOOD_INDEX == MAX_SIZE_FOOD) {
				GotoXY(103, 0);
				DrawPortal();
				if (snake[SIZE_SNAKE - 1].x == 100 && snake[SIZE_SNAKE - 1].y == 18) {
					snake[SIZE_SNAKE - 1].x = 100;
					snake[SIZE_SNAKE - 1].y = 90;
				}
				if (snake[0].x - 1 == 100 && snake[0].y == 90) {
					if (LEVEL == 4) {
						ProcessDead();
					}
					else {
						LEVEL++;
						ChangeLevel(LEVEL);
					}
				}
			}
		}
		Sleep((DWORD)(50 / SPEED));//Sleep function with SPEED variable
	}
}

void introGame() {
	system("color F0");
	SetColor(15, 9);
	SetConsoleOutputCP(852);
	SetColor(15, 6);
	GotoXY(0, 4);
	printMyFile("test.txt");
	GotoXY(90, 40);
	printMyFile("nhom.txt");
	for (int i = 69; i < 104; i++) {
		GotoXY(i, 34);
		cout << (char)205;
	}
	for (int i = 69; i < 104; i++) {
		GotoXY(i, 36);
		cout << (char)205;
	}
	GotoXY(68, 34); cout << (char)201;
	GotoXY(68, 35); cout << (char)186;
	GotoXY(68, 36); cout << (char)200;
	GotoXY(104, 34); cout << (char)187;
	GotoXY(104, 35); cout << (char)186;
	GotoXY(104, 36); cout << (char)188;
	GotoXY(71, 35);
	system("pause");
	system("cls");
}

void menuGame() {
	system("color F0");	
	SetConsoleOutputCP(852);
	SetColor(15, 11);
	printMyFile("snakemenu.txt");
	SetColor(15, 9);
	GotoXY(0, 2);
	printMyFile("menu.txt");
	SetColor(12, 15);
	for (int i = 65; i < 100; i++) {
		GotoXY(i, 13);
		cout << (char)205;
	}
	for (int i = 65; i < 100; i++) {
		GotoXY(i, 15);
		cout << (char)205;
	}
	GotoXY(64, 13); cout << (char)201;
	GotoXY(64, 14); cout << (char)186;
	GotoXY(64, 15); cout << (char)200;
	GotoXY(100, 13); cout << (char)187;
	GotoXY(100, 14); cout << (char)186;
	GotoXY(100, 15); cout << (char)188;
	GotoXY(65, 14); printf("             PLAY GAME             ");
	SetColor(15, 4);
	for (int i = 65; i < 100; i++) {
		GotoXY(i, 17);
		cout << (char)205;
	}
	for (int i = 65; i < 100; i++) {
		GotoXY(i, 19);
		cout << (char)205;
	}
	GotoXY(64, 17); cout << (char)201;
	GotoXY(64, 18); cout << (char)186;
	GotoXY(64, 19); cout << (char)200;
	GotoXY(100, 17); cout << (char)187;
	GotoXY(100, 18); cout << (char)186;
	GotoXY(100, 19); cout << (char)188;
	GotoXY(65, 18); printf("               HELP             ");
	for (int i = 65; i < 100; i++) {
		GotoXY(i, 21);
		cout << (char)205;
	}
	for (int i = 65; i < 100; i++) {
		GotoXY(i, 23);
		cout << (char)205;
	}
	GotoXY(64, 21); cout << (char)201;
	GotoXY(64, 22); cout << (char)186;
	GotoXY(64, 23); cout << (char)200;
	GotoXY(100, 21); cout << (char)187;
	GotoXY(100, 22); cout << (char)186;
	GotoXY(100, 23); cout << (char)188;
	GotoXY(65, 22); printf("               ABOUT               ");
	for (int i = 65; i < 100; i++) {
		GotoXY(i, 25);
		cout << (char)205;
	}
	for (int i = 65; i < 100; i++) {
		GotoXY(i, 27);
		cout << (char)205;
	}
	GotoXY(64, 25); cout << (char)201;
	GotoXY(64, 26); cout << (char)186;
	GotoXY(64, 27); cout << (char)200;
	GotoXY(100, 25); cout << (char)187;
	GotoXY(100, 26); cout << (char)186;
	GotoXY(100, 27); cout << (char)188;
	GotoXY(65, 26); printf("             LOAD GAME             ");
	for (int i = 65; i < 100; i++) {
		GotoXY(i, 29);
		cout << (char)205;
	}
	for (int i = 65; i < 100; i++) {
		GotoXY(i, 31);
		cout << (char)205;
	}
	GotoXY(64, 29); cout << (char)201;
	GotoXY(64, 30); cout << (char)186;
	GotoXY(64, 31); cout << (char)200;
	GotoXY(100, 29); cout << (char)187;
	GotoXY(100, 30); cout << (char)186;
	GotoXY(100, 31); cout << (char)188;
	GotoXY(65, 30); printf("             HIGH SCORE            ");
	for (int i = 65; i < 100; i++) {
		GotoXY(i, 33);
		cout << (char)205;
	}
	for (int i = 65; i < 100; i++) {
		GotoXY(i, 35);
		cout << (char)205;
	}
	GotoXY(64, 33); cout << (char)201;
	GotoXY(64, 34); cout << (char)186;
	GotoXY(64, 35); cout << (char)200;
	GotoXY(100, 33); cout << (char)187;
	GotoXY(100, 34); cout << (char)186;
	GotoXY(100, 35); cout << (char)188;
	GotoXY(65, 34); printf("               SETTING             ");
	for (int i = 65; i < 100; i++) {
		GotoXY(i, 37);
		cout << (char)205;
	}
	for (int i = 65; i < 100; i++) {
		GotoXY(i, 39);
		cout << (char)205;
	}
	GotoXY(64, 37); cout << (char)201;
	GotoXY(64, 38); cout << (char)186;
	GotoXY(64, 39); cout << (char)200;
	GotoXY(100, 37); cout << (char)187;
	GotoXY(100, 38); cout << (char)186;
	GotoXY(100, 39); cout << (char)188;
	GotoXY(65, 38); printf("                EXIT               ");
	GotoXY(78, 40);
	int chon = 0;
	int toado = 15;
	do {
		char a = _getch();
		if (a == 80 || a == 's' || a == 'S' || a == '2') chon = 1;
		else if (a == 72 || a == 'w' || a == 'W' || a == '8') chon = 2;
		else if (a == 13 || a == '5') chon = 3;
		else chon = 0;
		if (chon == 1 && toado < 21) toado++;
		else if (chon == 2 && toado > 15) toado--;
		if (toado == 15)
		{
			SetColor(12, 15);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 13);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 15);
				cout << (char)205;
			}
			GotoXY(64, 13); cout << (char)201;
			GotoXY(64, 14); cout << (char)186;
			GotoXY(64, 15); cout << (char)200;
			GotoXY(100, 13); cout << (char)187;
			GotoXY(100, 14); cout << (char)186;
			GotoXY(100, 15); cout << (char)188;
			GotoXY(65, 14); printf("             PLAY GAME             ");
			SetColor(15, 4);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 17);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 19);
				cout << (char)205;
			}
			GotoXY(64, 17); cout << (char)201;
			GotoXY(64, 18); cout << (char)186;
			GotoXY(64, 19); cout << (char)200;
			GotoXY(100, 17); cout << (char)187;
			GotoXY(100, 18); cout << (char)186;
			GotoXY(100, 19); cout << (char)188;
			GotoXY(65, 18); printf("               HELP                ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 21);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 23);
				cout << (char)205;
			}
			GotoXY(64, 21); cout << (char)201;
			GotoXY(64, 22); cout << (char)186;
			GotoXY(64, 23); cout << (char)200;
			GotoXY(100, 21); cout << (char)187;
			GotoXY(100, 22); cout << (char)186;
			GotoXY(100, 23); cout << (char)188;
			GotoXY(65, 22); printf("               ABOUT               ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 25);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 27);
				cout << (char)205;
			}
			GotoXY(64, 25); cout << (char)201;
			GotoXY(64, 26); cout << (char)186;
			GotoXY(64, 27); cout << (char)200;
			GotoXY(100, 25); cout << (char)187;
			GotoXY(100, 26); cout << (char)186;
			GotoXY(100, 27); cout << (char)188;
			GotoXY(65, 26); printf("             LOAD GAME             ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 29);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 31);
				cout << (char)205;
			}
			GotoXY(64, 29); cout << (char)201;
			GotoXY(64, 30); cout << (char)186;
			GotoXY(64, 31); cout << (char)200;
			GotoXY(100, 29); cout << (char)187;
			GotoXY(100, 30); cout << (char)186;
			GotoXY(100, 31); cout << (char)188;
			GotoXY(65, 30); printf("             HIGH SCORE            ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 33);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 35);
				cout << (char)205;
			}
			GotoXY(64, 33); cout << (char)201;
			GotoXY(64, 34); cout << (char)186;
			GotoXY(64, 35); cout << (char)200;
			GotoXY(100, 33); cout << (char)187;
			GotoXY(100, 34); cout << (char)186;
			GotoXY(100, 35); cout << (char)188;
			GotoXY(65, 34); printf("               SETTING             ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 37);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 39);
				cout << (char)205;
			}
			GotoXY(64, 37); cout << (char)201;
			GotoXY(64, 38); cout << (char)186;
			GotoXY(64, 39); cout << (char)200;
			GotoXY(100, 37); cout << (char)187;
			GotoXY(100, 38); cout << (char)186;
			GotoXY(100, 39); cout << (char)188;
			GotoXY(65, 38); printf("                EXIT               ");
		}
		if (toado == 16)
		{
			SetColor(15, 4);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 13);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 15);
				cout << (char)205;
			}
			GotoXY(64, 13); cout << (char)201;
			GotoXY(64, 14); cout << (char)186;
			GotoXY(64, 15); cout << (char)200;
			GotoXY(100, 13); cout << (char)187;
			GotoXY(100, 14); cout << (char)186;
			GotoXY(100, 15); cout << (char)188;
			GotoXY(65, 14); printf("             PLAY GAME             ");
			SetColor(12, 15);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 17);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 19);
				cout << (char)205;
			}
			GotoXY(64, 17); cout << (char)201;
			GotoXY(64, 18); cout << (char)186;
			GotoXY(64, 19); cout << (char)200;
			GotoXY(100, 17); cout << (char)187;
			GotoXY(100, 18); cout << (char)186;
			GotoXY(100, 19); cout << (char)188;
			GotoXY(65, 18); printf("               HELP                ");
			SetColor(15, 4);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 21);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 23);
				cout << (char)205;
			}
			GotoXY(64, 21); cout << (char)201;
			GotoXY(64, 22); cout << (char)186;
			GotoXY(64, 23); cout << (char)200;
			GotoXY(100, 21); cout << (char)187;
			GotoXY(100, 22); cout << (char)186;
			GotoXY(100, 23); cout << (char)188;
			GotoXY(65, 22); printf("               ABOUT               ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 25);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 27);
				cout << (char)205;
			}
			GotoXY(64, 25); cout << (char)201;
			GotoXY(64, 26); cout << (char)186;
			GotoXY(64, 27); cout << (char)200;
			GotoXY(100, 25); cout << (char)187;
			GotoXY(100, 26); cout << (char)186;
			GotoXY(100, 27); cout << (char)188;
			GotoXY(65, 26); printf("             LOAD GAME             ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 29);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 31);
				cout << (char)205;
			}
			GotoXY(64, 29); cout << (char)201;
			GotoXY(64, 30); cout << (char)186;
			GotoXY(64, 31); cout << (char)200;
			GotoXY(100, 29); cout << (char)187;
			GotoXY(100, 30); cout << (char)186;
			GotoXY(100, 31); cout << (char)188;
			GotoXY(65, 30); printf("             HIGH SCORE            ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 33);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 35);
				cout << (char)205;
			}
			GotoXY(64, 33); cout << (char)201;
			GotoXY(64, 34); cout << (char)186;
			GotoXY(64, 35); cout << (char)200;
			GotoXY(100, 33); cout << (char)187;
			GotoXY(100, 34); cout << (char)186;
			GotoXY(100, 35); cout << (char)188;
			GotoXY(65, 34); printf("               SETTING             ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 37);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 39);
				cout << (char)205;
			}
			GotoXY(64, 37); cout << (char)201;
			GotoXY(64, 38); cout << (char)186;
			GotoXY(64, 39); cout << (char)200;
			GotoXY(100, 37); cout << (char)187;
			GotoXY(100, 38); cout << (char)186;
			GotoXY(100, 39); cout << (char)188;
			GotoXY(65, 38); printf("                EXIT               ");
		}
		if (toado == 17)
		{
			SetColor(15, 4);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 13);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 15);
				cout << (char)205;
			}
			GotoXY(64, 13); cout << (char)201;
			GotoXY(64, 14); cout << (char)186;
			GotoXY(64, 15); cout << (char)200;
			GotoXY(100, 13); cout << (char)187;
			GotoXY(100, 14); cout << (char)186;
			GotoXY(100, 15); cout << (char)188;
			GotoXY(65, 14); printf("             PLAY GAME             ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 17);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 19);
				cout << (char)205;
			}
			GotoXY(64, 17); cout << (char)201;
			GotoXY(64, 18); cout << (char)186;
			GotoXY(64, 19); cout << (char)200;
			GotoXY(100, 17); cout << (char)187;
			GotoXY(100, 18); cout << (char)186;
			GotoXY(100, 19); cout << (char)188;
			GotoXY(65, 18); printf("               HELP                ");
			SetColor(12, 15);

			for (int i = 65; i < 100; i++) {
				GotoXY(i, 21);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 23);
				cout << (char)205;
			}
			GotoXY(64, 21); cout << (char)201;
			GotoXY(64, 22); cout << (char)186;
			GotoXY(64, 23); cout << (char)200;
			GotoXY(100, 21); cout << (char)187;
			GotoXY(100, 22); cout << (char)186;
			GotoXY(100, 23); cout << (char)188;
			GotoXY(65, 22); printf("               ABOUT               ");
			SetColor(15, 4);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 25);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 27);
				cout << (char)205;
			}
			GotoXY(64, 25); cout << (char)201;
			GotoXY(64, 26); cout << (char)186;
			GotoXY(64, 27); cout << (char)200;
			GotoXY(100, 25); cout << (char)187;
			GotoXY(100, 26); cout << (char)186;
			GotoXY(100, 27); cout << (char)188;
			GotoXY(65, 26); printf("             LOAD GAME             ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 29);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 31);
				cout << (char)205;
			}
			GotoXY(64, 29); cout << (char)201;
			GotoXY(64, 30); cout << (char)186;
			GotoXY(64, 31); cout << (char)200;
			GotoXY(100, 29); cout << (char)187;
			GotoXY(100, 30); cout << (char)186;
			GotoXY(100, 31); cout << (char)188;
			GotoXY(65, 30); printf("             HIGH SCORE            ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 33);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 35);
				cout << (char)205;
			}
			GotoXY(64, 33); cout << (char)201;
			GotoXY(64, 34); cout << (char)186;
			GotoXY(64, 35); cout << (char)200;
			GotoXY(100, 33); cout << (char)187;
			GotoXY(100, 34); cout << (char)186;
			GotoXY(100, 35); cout << (char)188;
			GotoXY(65, 34); printf("               SETTING             ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 37);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 39);
				cout << (char)205;
			}
			GotoXY(64, 37); cout << (char)201;
			GotoXY(64, 38); cout << (char)186;
			GotoXY(64, 39); cout << (char)200;
			GotoXY(100, 37); cout << (char)187;
			GotoXY(100, 38); cout << (char)186;
			GotoXY(100, 39); cout << (char)188;
			GotoXY(65, 38); printf("                EXIT               ");
		}
		if (toado == 18)
		{
			SetColor(15, 4);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 13);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 15);
				cout << (char)205;
			}
			GotoXY(64, 13); cout << (char)201;
			GotoXY(64, 14); cout << (char)186;
			GotoXY(64, 15); cout << (char)200;
			GotoXY(100, 13); cout << (char)187;
			GotoXY(100, 14); cout << (char)186;
			GotoXY(100, 15); cout << (char)188;
			GotoXY(65, 14); printf("             PLAY GAME             ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 17);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 19);
				cout << (char)205;
			}
			GotoXY(64, 17); cout << (char)201;
			GotoXY(64, 18); cout << (char)186;
			GotoXY(64, 19); cout << (char)200;
			GotoXY(100, 17); cout << (char)187;
			GotoXY(100, 18); cout << (char)186;
			GotoXY(100, 19); cout << (char)188;
			GotoXY(65, 18); printf("               HELP                ");


			for (int i = 65; i < 100; i++) {
				GotoXY(i, 21);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 23);
				cout << (char)205;
			}
			GotoXY(64, 21); cout << (char)201;
			GotoXY(64, 22); cout << (char)186;
			GotoXY(64, 23); cout << (char)200;
			GotoXY(100, 21); cout << (char)187;
			GotoXY(100, 22); cout << (char)186;
			GotoXY(100, 23); cout << (char)188;
			GotoXY(65, 22); printf("               ABOUT               ");
			SetColor(12, 15);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 25);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 27);
				cout << (char)205;
			}
			GotoXY(64, 25); cout << (char)201;
			GotoXY(64, 26); cout << (char)186;
			GotoXY(64, 27); cout << (char)200;
			GotoXY(100, 25); cout << (char)187;
			GotoXY(100, 26); cout << (char)186;
			GotoXY(100, 27); cout << (char)188;
			GotoXY(65, 26); printf("             LOAD GAME             ");
			SetColor(15, 4);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 29);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 31);
				cout << (char)205;
			}
			GotoXY(64, 29); cout << (char)201;
			GotoXY(64, 30); cout << (char)186;
			GotoXY(64, 31); cout << (char)200;
			GotoXY(100, 29); cout << (char)187;
			GotoXY(100, 30); cout << (char)186;
			GotoXY(100, 31); cout << (char)188;
			GotoXY(65, 30); printf("             HIGH SCORE            ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 33);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 35);
				cout << (char)205;
			}
			GotoXY(64, 33); cout << (char)201;
			GotoXY(64, 34); cout << (char)186;
			GotoXY(64, 35); cout << (char)200;
			GotoXY(100, 33); cout << (char)187;
			GotoXY(100, 34); cout << (char)186;
			GotoXY(100, 35); cout << (char)188;
			GotoXY(65, 34); printf("               SETTING             ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 37);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 39);
				cout << (char)205;
			}
			GotoXY(64, 37); cout << (char)201;
			GotoXY(64, 38); cout << (char)186;
			GotoXY(64, 39); cout << (char)200;
			GotoXY(100, 37); cout << (char)187;
			GotoXY(100, 38); cout << (char)186;
			GotoXY(100, 39); cout << (char)188;
			GotoXY(65, 38); printf("                EXIT               ");
		}
		if (toado == 19)
		{
			SetColor(15, 4);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 13);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 15);
				cout << (char)205;
			}
			GotoXY(64, 13); cout << (char)201;
			GotoXY(64, 14); cout << (char)186;
			GotoXY(64, 15); cout << (char)200;
			GotoXY(100, 13); cout << (char)187;
			GotoXY(100, 14); cout << (char)186;
			GotoXY(100, 15); cout << (char)188;
			GotoXY(65, 14); printf("             PLAY GAME             ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 17);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 19);
				cout << (char)205;
			}
			GotoXY(64, 17); cout << (char)201;
			GotoXY(64, 18); cout << (char)186;
			GotoXY(64, 19); cout << (char)200;
			GotoXY(100, 17); cout << (char)187;
			GotoXY(100, 18); cout << (char)186;
			GotoXY(100, 19); cout << (char)188;
			GotoXY(65, 18); printf("               HELP                ");


			for (int i = 65; i < 100; i++) {
				GotoXY(i, 21);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 23);
				cout << (char)205;
			}
			GotoXY(64, 21); cout << (char)201;
			GotoXY(64, 22); cout << (char)186;
			GotoXY(64, 23); cout << (char)200;
			GotoXY(100, 21); cout << (char)187;
			GotoXY(100, 22); cout << (char)186;
			GotoXY(100, 23); cout << (char)188;
			GotoXY(65, 22); printf("               ABOUT               ");

			for (int i = 65; i < 100; i++) {
				GotoXY(i, 25);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 27);
				cout << (char)205;
			}
			GotoXY(64, 25); cout << (char)201;
			GotoXY(64, 26); cout << (char)186;
			GotoXY(64, 27); cout << (char)200;
			GotoXY(100, 25); cout << (char)187;
			GotoXY(100, 26); cout << (char)186;
			GotoXY(100, 27); cout << (char)188;
			GotoXY(65, 26); printf("             LOAD GAME             ");
			SetColor(12, 15);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 29);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 31);
				cout << (char)205;
			}
			GotoXY(64, 29); cout << (char)201;
			GotoXY(64, 30); cout << (char)186;
			GotoXY(64, 31); cout << (char)200;
			GotoXY(100, 29); cout << (char)187;
			GotoXY(100, 30); cout << (char)186;
			GotoXY(100, 31); cout << (char)188;
			GotoXY(65, 30); printf("             HIGH SCORE            ");
			SetColor(15, 4);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 33);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 35);
				cout << (char)205;
			}
			GotoXY(64, 33); cout << (char)201;
			GotoXY(64, 34); cout << (char)186;
			GotoXY(64, 35); cout << (char)200;
			GotoXY(100, 33); cout << (char)187;
			GotoXY(100, 34); cout << (char)186;
			GotoXY(100, 35); cout << (char)188;
			GotoXY(65, 34); printf("               SETTING             ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 37);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 39);
				cout << (char)205;
			}
			GotoXY(64, 37); cout << (char)201;
			GotoXY(64, 38); cout << (char)186;
			GotoXY(64, 39); cout << (char)200;
			GotoXY(100, 37); cout << (char)187;
			GotoXY(100, 38); cout << (char)186;
			GotoXY(100, 39); cout << (char)188;
			GotoXY(65, 38); printf("                EXIT               ");
		}
		if (toado == 20)
		{
			SetColor(15, 4);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 13);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 15);
				cout << (char)205;
			}
			GotoXY(64, 13); cout << (char)201;
			GotoXY(64, 14); cout << (char)186;
			GotoXY(64, 15); cout << (char)200;
			GotoXY(100, 13); cout << (char)187;
			GotoXY(100, 14); cout << (char)186;
			GotoXY(100, 15); cout << (char)188;
			GotoXY(65, 14); printf("             PLAY GAME             ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 17);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 19);
				cout << (char)205;
			}
			GotoXY(64, 17); cout << (char)201;
			GotoXY(64, 18); cout << (char)186;
			GotoXY(64, 19); cout << (char)200;
			GotoXY(100, 17); cout << (char)187;
			GotoXY(100, 18); cout << (char)186;
			GotoXY(100, 19); cout << (char)188;
			GotoXY(65, 18); printf("               HELP                ");


			for (int i = 65; i < 100; i++) {
				GotoXY(i, 21);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 23);
				cout << (char)205;
			}
			GotoXY(64, 21); cout << (char)201;
			GotoXY(64, 22); cout << (char)186;
			GotoXY(64, 23); cout << (char)200;
			GotoXY(100, 21); cout << (char)187;
			GotoXY(100, 22); cout << (char)186;
			GotoXY(100, 23); cout << (char)188;
			GotoXY(65, 22); printf("               ABOUT               ");

			for (int i = 65; i < 100; i++) {
				GotoXY(i, 25);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 27);
				cout << (char)205;
			}
			GotoXY(64, 25); cout << (char)201;
			GotoXY(64, 26); cout << (char)186;
			GotoXY(64, 27); cout << (char)200;
			GotoXY(100, 25); cout << (char)187;
			GotoXY(100, 26); cout << (char)186;
			GotoXY(100, 27); cout << (char)188;
			GotoXY(65, 26); printf("             LOAD GAME             ");
			
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 29);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 31);
				cout << (char)205;
			}
			GotoXY(64, 29); cout << (char)201;
			GotoXY(64, 30); cout << (char)186;
			GotoXY(64, 31); cout << (char)200;
			GotoXY(100, 29); cout << (char)187;
			GotoXY(100, 30); cout << (char)186;
			GotoXY(100, 31); cout << (char)188;
			GotoXY(65, 30); printf("             HIGH SCORE            ");
			
			SetColor(12, 15);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 33);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 35);
				cout << (char)205;
			}
			GotoXY(64, 33); cout << (char)201;
			GotoXY(64, 34); cout << (char)186;
			GotoXY(64, 35); cout << (char)200;
			GotoXY(100, 33); cout << (char)187;
			GotoXY(100, 34); cout << (char)186;
			GotoXY(100, 35); cout << (char)188;
			GotoXY(65, 34); printf("               SETTING             ");
			SetColor(15, 4);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 37);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 39);
				cout << (char)205;
			}
			GotoXY(64, 37); cout << (char)201;
			GotoXY(64, 38); cout << (char)186;
			GotoXY(64, 39); cout << (char)200;
			GotoXY(100, 37); cout << (char)187;
			GotoXY(100, 38); cout << (char)186;
			GotoXY(100, 39); cout << (char)188;
			GotoXY(65, 38); printf("                EXIT               ");
		}
		if (toado == 21)
		{
			SetColor(15, 4);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 13);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 15);
				cout << (char)205;
			}
			GotoXY(64, 13); cout << (char)201;
			GotoXY(64, 14); cout << (char)186;
			GotoXY(64, 15); cout << (char)200;
			GotoXY(100, 13); cout << (char)187;
			GotoXY(100, 14); cout << (char)186;
			GotoXY(100, 15); cout << (char)188;
			GotoXY(65, 14); printf("             PLAY GAME             ");
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 17);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 19);
				cout << (char)205;
			}
			GotoXY(64, 17); cout << (char)201;
			GotoXY(64, 18); cout << (char)186;
			GotoXY(64, 19); cout << (char)200;
			GotoXY(100, 17); cout << (char)187;
			GotoXY(100, 18); cout << (char)186;
			GotoXY(100, 19); cout << (char)188;
			GotoXY(65, 18); printf("               HELP                ");


			for (int i = 65; i < 100; i++) {
				GotoXY(i, 21);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 23);
				cout << (char)205;
			}
			GotoXY(64, 21); cout << (char)201;
			GotoXY(64, 22); cout << (char)186;
			GotoXY(64, 23); cout << (char)200;
			GotoXY(100, 21); cout << (char)187;
			GotoXY(100, 22); cout << (char)186;
			GotoXY(100, 23); cout << (char)188;
			GotoXY(65, 22); printf("               ABOUT               ");

			for (int i = 65; i < 100; i++) {
				GotoXY(i, 25);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 27);
				cout << (char)205;
			}
			GotoXY(64, 25); cout << (char)201;
			GotoXY(64, 26); cout << (char)186;
			GotoXY(64, 27); cout << (char)200;
			GotoXY(100, 25); cout << (char)187;
			GotoXY(100, 26); cout << (char)186;
			GotoXY(100, 27); cout << (char)188;
			GotoXY(65, 26); printf("             LOAD GAME             ");

			for (int i = 65; i < 100; i++) {
				GotoXY(i, 29);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 31);
				cout << (char)205;
			}
			GotoXY(64, 29); cout << (char)201;
			GotoXY(64, 30); cout << (char)186;
			GotoXY(64, 31); cout << (char)200;
			GotoXY(100, 29); cout << (char)187;
			GotoXY(100, 30); cout << (char)186;
			GotoXY(100, 31); cout << (char)188;
			GotoXY(65, 30); printf("             HIGH SCORE            ");

			
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 33);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 35);
				cout << (char)205;
			}
			GotoXY(64, 33); cout << (char)201;
			GotoXY(64, 34); cout << (char)186;
			GotoXY(64, 35); cout << (char)200;
			GotoXY(100, 33); cout << (char)187;
			GotoXY(100, 34); cout << (char)186;
			GotoXY(100, 35); cout << (char)188;
			GotoXY(65, 34); printf("               SETTING             ");
			SetColor(12, 15);
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 37);
				cout << (char)205;
			}
			for (int i = 65; i < 100; i++) {
				GotoXY(i, 39);
				cout << (char)205;
			}
			GotoXY(64, 37); cout << (char)201;
			GotoXY(64, 38); cout << (char)186;
			GotoXY(64, 39); cout << (char)200;
			GotoXY(100, 37); cout << (char)187;
			GotoXY(100, 38); cout << (char)186;
			GotoXY(100, 39); cout << (char)188;
			GotoXY(65, 38); printf("                EXIT               ");
			SetColor(15, 4);
		}

	} while (chon != 3);
	system("cls");
	if (toado == 15) playGame(-1);
	else if (toado == 16) help();
	else if (toado == 17) about();
	else if (toado == 18) loadgame();
	else if (toado == 19) Score();
	else if (toado == 20) Setting();
	else if (toado == 21)
	{
		SetConsoleOutputCP(852);
		SetColor(15, 4);
		GotoXY(0, 6);
		printMyFile("exit.txt");
		for (int i = 69; i < 104; i++) {
			GotoXY(i, 34);
			cout << (char)205;
		}
		for (int i = 69; i < 104; i++) {
			GotoXY(i, 36);
			cout << (char)205;
		}
		GotoXY(68, 34); cout << (char)201;
		GotoXY(68, 35); cout << (char)186;
		GotoXY(68, 36); cout << (char)200;
		GotoXY(104, 34); cout << (char)187;
		GotoXY(104, 35); cout << (char)186;
		GotoXY(104, 36); cout << (char)188;
		GotoXY(71, 35);
		system("pause");
		exit(1);
		return;
	}

}

void help()
{
	system("cls");
	system("color F0");
	SetConsoleOutputCP(852);
	SetColor(15, 4);
	GotoXY(0, 6);
	printMyFile("help.txt");
	GotoXY(0, 20);
	SetColor(15, 4);
	printMyFile("control.txt");
	SetColor(15, 0);
	GotoXY(0, 20);
	printMyFile("guide.txt");
	GotoXY(6, 20); cout << (char)4;
	GotoXY(6, 22); cout << (char)4;
	GotoXY(6, 25); cout << (char)4;
	GotoXY(6, 28); cout << (char)4;
	GotoXY(6, 31); cout << (char)4;
	SetColor(15, 0);

	for (int i = 66; i < 104; i++) {
		for (int j = 19; j < 34; j++) {
			GotoXY(i, j);
			SetColor(15, 12); cout << (char)219;
		}
	}

	SetColor(12, 15);
	GotoXY(75, 21); cout << "'W'             " << (char)30;
	GotoXY(75, 23); cout << "'S'             " << (char)31;
	GotoXY(75, 25); cout << "'A'             " << (char)17;
	GotoXY(75, 27); cout << "'D'             " << (char)16;
	GotoXY(75, 29); cout << "'P'          " << "'PAUSE'";
	GotoXY(75, 31); cout << "ESC          " << "'EXIT'";

	char a;
	do
	{
		SetColor(15, 4);
		for (int i = 69; i < 103; i++) {
			GotoXY(i, 39);
			cout << (char)205;
		}
		for (int i = 69; i < 103; i++) {
			GotoXY(i, 41);
			cout << (char)205;
		}
		GotoXY(68, 39); cout << (char)201;
		GotoXY(68, 40); cout << (char)186;
		GotoXY(68, 41); cout << (char)200;
		GotoXY(103, 39); cout << (char)187;
		GotoXY(103, 40); cout << (char)186;
		GotoXY(103, 41); cout << (char)188;
		GotoXY(71, 40);
		cout << (char)16 << "  Press ENTER to back menu " << (char)17;
		a = _getch();
	} while (a != 13 && a != 'e' && a != 'E' && a != '5' && a != 8);
	system("cls");
	fflush(stdin);
	menuGame();
}

void Score()
{
	system("cls");
	system("color F0");
	SetConsoleOutputCP(852);
	SetColor(15, 4);
	GotoXY(0, 6);
	printMyFile("highscore.txt");
	GotoXY(20, 18);
	SetColor(15, 4);

	printMyFile("ranking.txt");
	SetColor(15, 0);

	for (int i = 80; i < 135; i++) {
		GotoXY(i, 18); cout << (char)205;
		GotoXY(i, 20); cout << (char)205;
		GotoXY(i, 32); cout << (char)205;
	}
	for (int i = 18; i < 33; i++) {
		GotoXY(80, i); cout << (char)186;
		GotoXY(90, i); cout << (char)186;
		GotoXY(120, i); cout << (char)186;
		GotoXY(134, i); cout << (char)186;
	}

	GotoXY(80, 18); cout << (char)201;
	GotoXY(80, 32); cout << (char)200;
	GotoXY(80, 20); cout << (char)204;
	GotoXY(90, 18); cout << (char)203;
	GotoXY(90, 32); cout << (char)202;
	GotoXY(90, 20); cout << (char)206;
	GotoXY(120, 18); cout << (char)203;
	GotoXY(120, 32); cout << (char)202;
	GotoXY(120, 20); cout << (char)206;
	GotoXY(134, 20); cout << (char)185;
	GotoXY(134, 18); cout << (char)187;
	GotoXY(134, 32); cout << (char)188;

	GotoXY(103, 19); cout << "NAME";
	GotoXY(125, 19); cout << "SCORE";

	readFileScore(saveNameScore, (char*)nameFile1);

	
	for (int i = 0; i < saveNameScore.size; i++) {
		arrTemp[i] = saveNameScore.score[i];
		arrNameTemp[i] = saveNameScore.namePlay[i];
	}
	for (int i = 0; i < saveNameScore.size - 1; i++) {
		for (int j = 0; j < saveNameScore.size - i - 1; j++) {
			if (arrTemp[j] < arrTemp[j + 1]) {
				// Hoán đổi nếu phần tử hiện tại nhỏ hơn phần tử tiếp theo
				int temp = arrTemp[j];
				arrTemp[j] = arrTemp[j + 1];
				arrTemp[j + 1] = temp;
				string nameTemp = arrNameTemp[j];
				arrNameTemp[j] = arrNameTemp[j + 1];
				arrNameTemp[j + 1] = nameTemp;
			}
		}
	}
		GotoXY(84, 19); cout << "TOP";
		GotoXY(83, 22); cout << "TOP 1";
		GotoXY(83, 24); cout << "TOP 2";
		GotoXY(83, 26); cout << "TOP 3";
		GotoXY(83, 28); cout << "TOP 4";
		GotoXY(83, 30); cout << "TOP 5";


		GotoXY(95, 22); cout << arrNameTemp[0];
		GotoXY(95, 24); cout << arrNameTemp[1];
		GotoXY(95, 26); cout << arrNameTemp[2];
		GotoXY(95, 28); cout << arrNameTemp[3];
		GotoXY(95, 30); cout << arrNameTemp[4];

		if (arrTemp[0] <= 0) {
			GotoXY(123, 22); cout << "No data";
		}
		else {
			GotoXY(123, 22); cout << arrTemp[0];
		}
		if (arrTemp[1] <= 0) {
			GotoXY(123, 24); cout << "No data";
		}
		else {
			GotoXY(123, 24); cout << arrTemp[1];
		}
		if (arrTemp[2] <= 0) {
			GotoXY(123, 26); cout << "No data";
		}
		else {
			GotoXY(123, 26); cout << arrTemp[2];
		}
		if (arrTemp[3] <= 0) {
			GotoXY(123, 28); cout << "No data";
		}
		else {
			GotoXY(123, 28); cout << arrTemp[3];
		}
		if (arrTemp[4] <= 0) {
			GotoXY(123, 30); cout << "No data";
		}
		else {
			GotoXY(123, 30); cout << arrTemp[4];
		}

	char a;
	do
	{
		SetColor(15, 4);
		for (int i = 69; i < 103; i++) {
			GotoXY(i, 39);
			cout << (char)205;
		}
		for (int i = 69; i < 103; i++) {
			GotoXY(i, 41);
			cout << (char)205;
		}
		GotoXY(68, 39); cout << (char)201;
		GotoXY(68, 40); cout << (char)186;
		GotoXY(68, 41); cout << (char)200;
		GotoXY(103, 39); cout << (char)187;
		GotoXY(103, 40); cout << (char)186;
		GotoXY(103, 41); cout << (char)188;
		GotoXY(71, 40);
		cout << (char)16 << "  Press ENTER to back menu " << (char)17;
		a = _getch();
	} while (a != 13 && a != 'e' && a != 'E' && a != '5' && a != 8);
	system("cls");
	fflush(stdin);
	menuGame();
}

void loadgame()
{
	system("cls");
	system("color F0");
	SetConsoleOutputCP(852);
	SetColor(15, 4);
	GotoXY(0, 6);
	printMyFile("loadgame.txt");
	SetColor(15, 0);

	readFileName(saveName, (char*)nameFile);

	SetColor(15, 4);
	for (int i = 69; i < 103; i++) {
		GotoXY(i, 39);
		cout << (char)205;
	}
	for (int i = 69; i < 103; i++) {
		GotoXY(i, 41);
		cout << (char)205;
	}
	GotoXY(68, 39); cout << (char)201;
	GotoXY(68, 40); cout << (char)186;
	GotoXY(68, 41); cout << (char)200;
	GotoXY(103, 39); cout << (char)187;
	GotoXY(103, 40); cout << (char)186;
	GotoXY(103, 41); cout << (char)188;
	GotoXY(71, 40);
	cout << (char)16 << "   Press B to back menu  " << (char)17;

	for (int i = 20; i < 141; i++) {
		GotoXY(i, 14);
		cout << (char)205;
		GotoXY(i, 36);
		cout << (char)205;
		GotoXY(i, 18);
		cout << (char)205;
	}
	for (int i = 14; i < 37; i++) {
		GotoXY(20, i);
		cout << (char)186;
		GotoXY(28, i);
		cout << (char)186;
		GotoXY(60, i);
		cout << (char)186;
		GotoXY(68, i);
		cout << (char)186;
		GotoXY(100, i);
		cout << (char)186;
		GotoXY(108, i);
		cout << (char)186;
		GotoXY(140, i);
		cout << (char)186;

	}
	GotoXY(20, 14); cout << (char)201;
	GotoXY(20, 18); cout << (char)204;
	GotoXY(20, 36); cout << (char)200;
	GotoXY(28, 14); cout << (char)203;
	GotoXY(28, 18); cout << (char)206;
	GotoXY(28, 36); cout << (char)202;
	GotoXY(60, 14); cout << (char)203;
	GotoXY(60, 18); cout << (char)206;
	GotoXY(60, 36); cout << (char)202;
	GotoXY(68, 14); cout << (char)203;
	GotoXY(68, 18); cout << (char)206;
	GotoXY(68, 36); cout << (char)202;
	GotoXY(100, 14); cout << (char)203;
	GotoXY(100, 18); cout << (char)206;
	GotoXY(100, 36); cout << (char)202;
	GotoXY(108, 14); cout << (char)203;
	GotoXY(108, 18); cout << (char)206;
	GotoXY(108, 36); cout << (char)202;
	GotoXY(140, 14); cout << (char)187;
	GotoXY(140, 18); cout << (char)185;
	GotoXY(140, 36); cout << (char)188;

	GotoXY(23, 16); cout << "STT";
	GotoXY(63, 16); cout << "STT";
	GotoXY(103, 16); cout << "STT";
	GotoXY(40, 16); cout << "FILE NAME";
	GotoXY(80, 16); cout << "FILE NAME";
	GotoXY(120, 16); cout << "FILE NAME";


	if (saveName.size <= 15) {
		int pos = 20;
		for (int i = 0; i < saveName.size; i++) {
			if (i < 9) {
				GotoXY(23, pos);
				cout << "0" << i + 1;
			}
			else {
				GotoXY(23, pos);
				cout << i + 1;
			}
			GotoXY(40, pos); cout << saveName.name[i];
			pos++;
		}
	}
	else if (saveName.size > 15 && saveName.size <= 30) {
		int pos = 20;
		for (int i = 0; i < 15; i++) {
			if (i < 9) {
				GotoXY(23, pos);
				cout << "0" << i + 1;
			}
			else {
				GotoXY(23, pos);
				cout << i + 1;
			}
			GotoXY(40, pos); cout << saveName.name[i];
			pos++;
		}
		pos = 20;
		for (int i = 15; i < saveName.size; i++) {
			GotoXY(63, pos); cout << i + 1;

			GotoXY(80, pos); cout << saveName.name[i];
			pos++;
		}
	}
	else {
		int pos = 20;
		for (int i = 0; i < 15; i++) {
			if (i < 9) {
				GotoXY(23, pos);
				cout << "0" << i + 1;
			}
			else {
				GotoXY(23, pos);
				cout << i + 1;
			}
			GotoXY(20, pos); cout << saveName.name[i];
			pos++;
		}
		pos = 20;
		for (int i = 15; i < 30; i++) {
			GotoXY(63, pos); cout << i + 1;

			GotoXY(80, pos); cout << saveName.name[i];
			pos++;
		}
		pos = 20;
		for (int i = 30; i < saveName.size; i++) {
			GotoXY(103, pos); cout << i + 1;

			GotoXY(120, pos); cout << saveName.name[i];
			pos++;
		}
	}
	int chon = 0;
	int toado = 0;

	GotoXY(29, 20); cout << (char)175 << (char)175;
	do {
		char b = _getch();
		if (b == 'B' || b == 'b') {
			system("cls");
			menuGame();
		}
		else if (b == 80 || b == 's' || b == 'S' || b == '2') chon = 1;
		else if (b == 72 || b == 'w' || b == 'W' || b == '8') chon = 2;
		else if (b == 13 || b == '5') chon = 3;
		else chon = 0;
		if (chon == 1 && toado < saveName.size) toado++;
		else if (chon == 2 && toado > 0) toado--;

		if (toado == 0 && toado < saveName.size) {
			GotoXY(29, 20); cout << (char)175 << (char)175;
			GotoXY(29, 21); cout << "  ";
		}
		if (toado == 1 && toado < saveName.size) {
			GotoXY(29, 20); cout << "  ";
			GotoXY(29, 21); cout << (char)175 << (char)175;
			GotoXY(29, 22); cout << "  ";
		}
		if (toado == 2 && toado < saveName.size) {
			GotoXY(29, 21); cout << "  ";
			GotoXY(29, 22); cout << (char)175 << (char)175;
			GotoXY(29, 23); cout << "  ";
		}
		if (toado == 3 && toado < saveName.size) {
			GotoXY(29, 22); cout << "  ";
			GotoXY(29, 23); cout << (char)175 << (char)175;
			GotoXY(29, 24); cout << "  ";
		}
		if (toado == 4 && toado < saveName.size) {
			GotoXY(29, 23); cout << "  ";
			GotoXY(29, 24); cout << (char)175 << (char)175;
			GotoXY(29, 25); cout << "  ";
		}
		if (toado == 5 && toado < saveName.size) {
			GotoXY(29, 24); cout << "  ";
			GotoXY(29, 25); cout << (char)175 << (char)175;
			GotoXY(29, 26); cout << "  ";
		}
		if (toado == 6 && toado < saveName.size) {
			GotoXY(29, 25); cout << "  ";
			GotoXY(29, 26); cout << (char)175 << (char)175;
			GotoXY(29, 27); cout << "  ";
		}
		if (toado == 7 && toado < saveName.size) {
			GotoXY(29, 26); cout << "  ";
			GotoXY(29, 27); cout << (char)175 << (char)175;
			GotoXY(29, 28); cout << "  ";
		}
		if (toado == 8 && toado < saveName.size) {
			GotoXY(29, 27); cout << "  ";
			GotoXY(29, 28); cout << (char)175 << (char)175;
			GotoXY(29, 29); cout << "  ";
		}
		if (toado == 9 && toado < saveName.size) {
			GotoXY(29, 28); cout << "  ";
			GotoXY(29, 29); cout << (char)175 << (char)175;
			GotoXY(29, 30); cout << "  ";
		}
		if (toado == 10 && toado < saveName.size) {
			GotoXY(29, 29); cout << "  ";
			GotoXY(29, 30); cout << (char)175 << (char)175;
			GotoXY(29, 31); cout << "  ";
		}
		if (toado == 11 && toado < saveName.size) {
			GotoXY(29, 30); cout << "  ";
			GotoXY(29, 31); cout << (char)175 << (char)175;
			GotoXY(29, 32); cout << "  ";
		}
		if (toado == 12 && toado < saveName.size) {
			GotoXY(29, 31); cout << "  ";
			GotoXY(29, 32); cout << (char)175 << (char)175;
			GotoXY(29, 33); cout << "  ";
		}
		if (toado == 13 && toado < saveName.size) {
			GotoXY(29, 32); cout << "  ";
			GotoXY(29, 33); cout << (char)175 << (char)175;
			GotoXY(29, 34); cout << "  ";
		}
		if (toado == 14 && toado < saveName.size) {
			GotoXY(29, 33); cout << "  ";
			GotoXY(29, 34); cout << (char)175 << (char)175;
			GotoXY(29, 35); cout << "  ";
			GotoXY(69, 20); cout << "  ";

		}
		if (toado == 15 && toado < saveName.size) {
			GotoXY(29, 35); cout << "  ";
			GotoXY(29, 34); cout << "  ";
			GotoXY(69, 20); cout << (char)175 << (char)175;
			GotoXY(69, 21); cout << "  ";
		}
		if (toado == 16 && toado < saveName.size) {
			GotoXY(69, 20); cout << "  ";
			GotoXY(69, 21); cout << (char)175 << (char)175;
			GotoXY(69, 22); cout << "  ";
		}
		if (toado == 17 && toado < saveName.size) {
			GotoXY(69, 21); cout << "  ";
			GotoXY(69, 22); cout << (char)175 << (char)175;
			GotoXY(69, 23); cout << "  ";
		}
		if (toado == 18 && toado < saveName.size) {
			GotoXY(69, 22); cout << "  ";
			GotoXY(69, 23); cout << (char)175 << (char)175;
			GotoXY(69, 24); cout << "  ";
		}
		if (toado == 19 && toado < saveName.size) {
			GotoXY(69, 23); cout << "  ";
			GotoXY(69, 24); cout << (char)175 << (char)175;
			GotoXY(69, 25); cout << "  ";
		}
		if (toado == 20 && toado < saveName.size) {
			GotoXY(69, 24); cout << "  ";
			GotoXY(69, 25); cout << (char)175 << (char)175;
			GotoXY(69, 26); cout << "  ";
		}
		if (toado == 21 && toado < saveName.size) {
			GotoXY(69, 25); cout << "  ";
			GotoXY(69, 26); cout << (char)175 << (char)175;
			GotoXY(69, 27); cout << "  ";
		}
		if (toado == 22 && toado < saveName.size) {
			GotoXY(69, 26); cout << "  ";
			GotoXY(69, 27); cout << (char)175 << (char)175;
			GotoXY(69, 28); cout << "  ";
		}
		if (toado == 23 && toado < saveName.size) {
			GotoXY(69, 27); cout << "  ";
			GotoXY(69, 28); cout << (char)175 << (char)175;
			GotoXY(69, 29); cout << "  ";
		}
		if (toado == 24 && toado < saveName.size) {
			GotoXY(69, 28); cout << "  ";
			GotoXY(69, 29); cout << (char)175 << (char)175;
			GotoXY(69, 30); cout << "  ";
		}
		if (toado == 25 && toado < saveName.size) {
			GotoXY(69, 29); cout << "  ";
			GotoXY(69, 30); cout << (char)175 << (char)175;
			GotoXY(69, 31); cout << "  ";
		}
		if (toado == 26 && toado < saveName.size) {
			GotoXY(69, 30); cout << "  ";
			GotoXY(69, 31); cout << (char)175 << (char)175;
			GotoXY(69, 32); cout << "  ";
		}
		if (toado == 27 && toado < saveName.size) {
			GotoXY(69, 31); cout << "  ";
			GotoXY(69, 32); cout << (char)175 << (char)175;
			GotoXY(69, 33); cout << "  ";
		}
		if (toado == 28 && toado < saveName.size) {
			GotoXY(69, 32); cout << "  ";
			GotoXY(69, 33); cout << (char)175 << (char)175;
			GotoXY(69, 34); cout << "  ";
		}
		if (toado == 29 && toado < saveName.size) {
			GotoXY(69, 33); cout << "  ";
			GotoXY(69, 34); cout << (char)175 << (char)175;
			GotoXY(69, 35); cout << "  ";
			GotoXY(109, 20); cout << "  ";

		}
		if (toado == 30 && toado < saveName.size) {
			GotoXY(109, 34); cout << "  ";
			GotoXY(109, 35); cout << "  ";
			GotoXY(109, 20); cout << (char)175 << (char)175;
			GotoXY(109, 21); cout << "  ";
		}
		if (toado == 31 && toado < saveName.size) {
			GotoXY(109, 20); cout << "  ";
			GotoXY(109, 21); cout << (char)175 << (char)175;
			GotoXY(109, 22); cout << "  ";
		}
		if (toado == 32 && toado < saveName.size) {
			GotoXY(109, 21); cout << "  ";
			GotoXY(109, 22); cout << (char)175 << (char)175;
			GotoXY(109, 23); cout << "  ";
		}
		if (toado == 33 && toado < saveName.size) {
			GotoXY(109, 22); cout << "  ";
			GotoXY(109, 23); cout << (char)175 << (char)175;
			GotoXY(109, 24); cout << "  ";
		}
		if (toado == 34 && toado < saveName.size) {
			GotoXY(109, 23); cout << "  ";
			GotoXY(109, 24); cout << (char)175 << (char)175;
			GotoXY(109, 25); cout << "  ";
		}
		if (toado == 35 && toado < saveName.size) {
			GotoXY(109, 24); cout << "  ";
			GotoXY(109, 25); cout << (char)175 << (char)175;
			GotoXY(109, 26); cout << "  ";
		}
		if (toado == 36 && toado < saveName.size) {
			GotoXY(109, 25); cout << "  ";
			GotoXY(109, 26); cout << (char)175 << (char)175;
			GotoXY(109, 27); cout << "  ";
		}
		if (toado == 37 && toado < saveName.size) {
			GotoXY(109, 26); cout << "  ";
			GotoXY(109, 27); cout << (char)175 << (char)175;
			GotoXY(109, 28); cout << "  ";
		}
		if (toado == 38 && toado < saveName.size) {
			GotoXY(109, 27); cout << "  ";
			GotoXY(109, 28); cout << (char)175 << (char)175;
			GotoXY(109, 29); cout << "  ";
		}
		if (toado == 39 && toado < saveName.size) {
			GotoXY(109, 28); cout << "  ";
			GotoXY(109, 29); cout << (char)175 << (char)175;
			GotoXY(109, 30); cout << "  ";
		}
		if (toado == 40 && toado < saveName.size) {
			GotoXY(109, 29); cout << "  ";
			GotoXY(109, 30); cout << (char)175 << (char)175;
			GotoXY(109, 31); cout << "  ";
		}
		if (toado == 41 && toado < saveName.size) {
			GotoXY(109, 30); cout << "  ";
			GotoXY(109, 31); cout << (char)175 << (char)175;
			GotoXY(109, 32); cout << "  ";
		}
		if (toado == 42 && toado < saveName.size) {
			GotoXY(109, 31); cout << "  ";
			GotoXY(109, 32); cout << (char)175 << (char)175;
			GotoXY(109, 33); cout << "  ";
		}
		if (toado == 43 && toado < saveName.size) {
			GotoXY(109, 32); cout << "  ";
			GotoXY(109, 33); cout << (char)175 << (char)175;
			GotoXY(109, 34); cout << "  ";
		}
		if (toado == 44 && toado < saveName.size) {
			GotoXY(109, 33); cout << "  ";
			GotoXY(109, 34); cout << (char)175 << (char)175;
			GotoXY(109, 35); cout << "  ";
		}


	} while (chon != 3);
	if (toado >= 0 && toado <= saveName.size) {
		const char* temp1 = (saveName.name[toado]).c_str();
		docfile(luusnake, (char*)temp1);
		playGame(1);
	}
}

void about()
{
	system("cls");
	system("color F0");
	SetConsoleOutputCP(852);
	SetColor(15, 4);
	GotoXY(0, 6);
	printMyFile("about.txt");
	SetColor(15, 0);

	SetColor(15, 0);
	GotoXY(0, 19);
	printMyFile("introduction.txt");

	char a;
	do
	{
		SetColor(15, 4);
		for (int i = 69; i < 103; i++) {
			GotoXY(i, 34);
			cout << (char)205;
		}
		for (int i = 69; i < 103; i++) {
			GotoXY(i, 36);
			cout << (char)205;
		}
		GotoXY(68, 34); cout << (char)201;
		GotoXY(68, 35); cout << (char)186;
		GotoXY(68, 36); cout << (char)200;
		GotoXY(103, 34); cout << (char)187;
		GotoXY(103, 35); cout << (char)186;
		GotoXY(103, 36); cout << (char)188;
		GotoXY(71, 35);
		cout << (char)16 << "  Press ENTER to back menu " << (char)17;
		a = _getch();
	} while (a != 13 && a != 'e' && a != 'E' && a != '5' && a != 8);
	system("cls");
	fflush(stdin);
	menuGame();
}

void Setting() {
	system("cls");
	system("color F0");

	SetConsoleOutputCP(852);
	SetColor(15, 4);
	SetColor(15, 4);
	for (int i = 69; i < 103; i++) {
		GotoXY(i, 39);
		cout << (char)205;
	}
	for (int i = 69; i < 103; i++) {
		GotoXY(i, 41);
		cout << (char)205;
	}
	GotoXY(68, 39); cout << (char)201;
	GotoXY(68, 40); cout << (char)186;
	GotoXY(68, 41); cout << (char)200;
	GotoXY(103, 39); cout << (char)187;
	GotoXY(103, 40); cout << (char)186;
	GotoXY(103, 41); cout << (char)188;
	GotoXY(71, 40);
	cout << (char)16 << "    Press B to back menu   " << (char)17;
	GotoXY(0, 6);
	printMyFile("setting.txt");
	SetColor(15, 0);

	GotoXY(0, 18);
	printMyFile("offvolume.txt");
	SetColor(15, 10);
	GotoXY(0, 18);
	printMyFile("onvolume.txt");
	int chon = 0;
	int toado = 0;
	do {
		char a = _getch();
		if (a == 80 || a == 'a' || a == 'A' || a == '4') chon = 2;
		else if (a == 72 || a == 'd' || a == 'D' || a == '6') chon = 1;
		else if (a == 13 || a == '5') chon = 3;
		else if (a == 'B' || a == 'b') chon = 4;
		else chon = 0;
		if (chon == 1 && toado < 1) toado++;
		else if (chon == 2 && toado > 0) toado--;
		if (toado == 0) {
			SetColor(15, 0);
			GotoXY(0, 18);
			printMyFile("offvolume.txt");
			SetColor(15, 10);
			GotoXY(0, 18);
			printMyFile("onvolume.txt");
		}
		if (toado == 1) {
			SetColor(15, 10);
			GotoXY(0, 18);
			printMyFile("offvolume.txt");
			SetColor(15, 0);
			GotoXY(0, 18);
			printMyFile("onvolume.txt");
		}
		if (chon == 3) {
			if (toado == 1) {
				StopBackgroundMusic();
			}
			if (toado == 0) {
				backgroundSound();
			}
		}	
	} while (chon != 4);

	system("cls");
	fflush(stdin);
	menuGame();
}

void playGame(int x) {
	if (x == -1) {
		system("cls");
		SetColor(15, 4);
		for (int i = 66; i < 100; i++) {
			GotoXY(i, 16);
			cout << (char)205;
			GotoXY(i, 23);
			cout << (char)205;
		}
		for (int i = 16; i < 24; i++) {
			GotoXY(65, i);
			cout << (char)186;
			GotoXY(100, i);
			cout << (char)186;
		}
		GotoXY(65, 16); cout << (char)201;
		GotoXY(65, 23); cout << (char)200;
		GotoXY(100, 16); cout << (char)187;
		GotoXY(100, 23); cout << (char)188;
		SetColor(15, 0);
		char testTempA[20];
		GotoXY(72, 18);
		cout << "Input your name player: \n";
		GotoXY(78, 20);
		cin.getline(testTempA, 21);
		if (checkNameScore(saveNameScore, testTempA)) {
			do {
				GotoXY(68, 18);
				cout << "Input your name player again: \n";
				GotoXY(78, 20);
				cout << "                ";
				GotoXY(78, 20);
				cin.getline(testTempA, 21);
			} while (checkNameScore(saveNameScore, testTempA));
		}
		saveNameScore.size++;
		saveNameScore.namePlay[saveNameScore.size - 1] = testTempA;
		writeFileScore(saveNameScore, (char*)nameFile1);
		system("cls");

		int temp;
		StartGame();
		settingObstacle();
		thread t1(ThreadFunc); //Create thread for snake

		HANDLE handle_t1 = t1.native_handle(); //Take handle of thread

		while (1) {
			temp = toupper(_getch());
			if (STATE == 1) {
				if (temp == 'P') {
					saveNameScore.score[saveNameScore.size - 1] = SCORE;
					writeFileScore(saveNameScore, (char*)nameFile1);
					PauseGame(handle_t1);
				}
				else if (temp == 27) {
					saveNameScore.score[saveNameScore.size - 1] = SCORE;
					writeFileScore(saveNameScore, (char*)nameFile1);
					TerminateThread(handle_t1, 0);
					system("cls");
					menuGame();
				}
				else if (temp == 'L') {
					saveNameScore.score[saveNameScore.size - 1] = SCORE;
					writeFileScore(saveNameScore, (char*)nameFile1);
					TerminateThread(handle_t1, 0);
					system("cls");
					SetColor(15, 4);
					for (int i = 66; i < 100; i++) {
						GotoXY(i, 16);
						cout << (char)205;
						GotoXY(i, 23);
						cout << (char)205;
					}
					for (int i = 16; i < 24; i++) {
						GotoXY(65, i);
						cout << (char)186;
						GotoXY(100, i);
						cout << (char)186;
					}
					GotoXY(65, 16); cout << (char)201;
					GotoXY(65, 23); cout << (char)200;
					GotoXY(100, 16); cout << (char)187;
					GotoXY(100, 23); cout << (char)188;
					SetColor(15, 0);
					char testTemp[20];
					GotoXY(72, 18);
					cout << "Input your name file: \n";
					GotoXY(75, 20);
					cin.getline(testTemp, 21);
					do {
						if (checkName(saveName, testTemp)) {
							GotoXY(68, 18);
							cout << "Input your name file again: \n";
							GotoXY(78, 20);
							cout << "                ";
							GotoXY(78, 20);
							cin.getline(testTemp, 21);
						}
					} while (checkName(saveName, testTemp));
					saveName.size++;
					saveName.name[saveName.size - 1] = testTemp;
					writeFileName(saveName, (char*)nameFile);
					ghifile(luusnake, testTemp);
					system("cls");
					menuGame();
				}
				else {
					ResumeThread(handle_t1);
					if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp ==
						'W' || temp == 'S'))
					{
						if (temp == 'D') CHAR_LOCK = 'A';
						else if (temp == 'W') CHAR_LOCK = 'S';
						else if (temp == 'S') CHAR_LOCK = 'W';
						else CHAR_LOCK = 'D';
						MOVING = temp;

					}

				}

			}
			else {
				saveNameScore.score[saveNameScore.size - 1] = SCORE;
				writeFileScore(saveNameScore, (char*)nameFile1);
				if (temp == 'Y' || temp == 'y') {
					system("cls");
					SetColor(15, 4);
					for (int i = 66; i < 100; i++) {
						GotoXY(i, 16);
						cout << (char)205;
						GotoXY(i, 23);
						cout << (char)205;
					}
					for (int i = 16; i < 24; i++) {
						GotoXY(65, i);
						cout << (char)186;
						GotoXY(100, i);
						cout << (char)186;
					}
					GotoXY(65, 16); cout << (char)201;
					GotoXY(65, 23); cout << (char)200;
					GotoXY(100, 16); cout << (char)187;
					GotoXY(100, 23); cout << (char)188;
					SetColor(15, 0);
					char testTemp1[20];
					GotoXY(72, 18);
					cout << "Input your name player: \n";
					GotoXY(75, 20);
					cin.getline(testTemp1, 21);
					if (checkNameScore(saveNameScore, testTemp1)) {
						do {
							GotoXY(68, 18);
							cout << "Input your name player again: \n";
							GotoXY(78, 20);
							cout << "                ";
							GotoXY(78, 20);
							cin.getline(testTemp1, 21);
						} while (checkNameScore(saveNameScore, testTemp1));
					}
					saveNameScore.size++;
					saveNameScore.namePlay[saveName.size - 1] = testTemp1;
					writeFileScore(saveNameScore, (char*)nameFile1);
					system("cls");
					StartGame();
				}
				else if (temp == 'B' || temp == 'b') {
					TerminateThread(handle_t1, 0);
					system("cls");
					menuGame();
				}

			}

		}
	}
	else if (x >= 0) {
		system("cls");
		int temp;
		StartGame();
		settingObstacle();
		StartGameLoad();
		std::thread t1(ThreadFunc); //Create thread for snake
		HANDLE handle_t1 = t1.native_handle(); //Take handle of thread
		while (1) {
			temp = toupper(_getch());
			if (STATE == 1) {
				if (temp == 'P') {
					saveNameScore.score[saveNameScore.size - 1] = SCORE;
					writeFileScore(saveNameScore, (char*)nameFile1);
					PauseGame(handle_t1);
				}
				else if (temp == 27) {
					saveNameScore.score[saveNameScore.size - 1] = SCORE;
					writeFileScore(saveNameScore, (char*)nameFile1);
					TerminateThread(handle_t1, 0);
					system("cls");
					menuGame();
				}
				else if (temp == 'L') {
					saveNameScore.score[saveNameScore.size - 1] = SCORE;
					writeFileScore(saveNameScore, (char*)nameFile1);
					TerminateThread(handle_t1, 0);
					system("cls");
					SetColor(15, 4);
					for (int i = 66; i < 100; i++) {
						GotoXY(i, 16);
						cout << (char)205;
						GotoXY(i, 23);
						cout << (char)205;
					}
					for (int i = 16; i < 24; i++) {
						GotoXY(65, i);
						cout << (char)186;
						GotoXY(100, i);
						cout << (char)186;
					}
					GotoXY(65, 16); cout << (char)201;
					GotoXY(65, 23); cout << (char)200;
					GotoXY(100, 16); cout << (char)187;
					GotoXY(100, 23); cout << (char)188;
					SetColor(15, 0);
					char testTemp[20];
					GotoXY(72, 18);
					cout << "Input your name file: \n";
					GotoXY(78, 20);
					cin.getline(testTemp, 21);
					do {
						if (checkName(saveName, testTemp)) {
							GotoXY(68, 18);
							cout << "Input your name file again: \n";
							GotoXY(78, 20);
							cout << "                ";
							GotoXY(78, 20);
							cin.getline(testTemp, 21);
						}
					} while (checkName(saveName, testTemp));
					saveName.size++;
					saveName.name[saveName.size - 1] = testTemp;
					writeFileName(saveName, (char*)nameFile);
					ghifile(luusnake, testTemp);
					system("cls");
					menuGame();
				}
				else {
					ResumeThread(handle_t1);
					if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S'))
					{
						if (temp == 'D') CHAR_LOCK = 'A';
						else if (temp == 'W') CHAR_LOCK = 'S';
						else if (temp == 'S') CHAR_LOCK = 'W';
						else CHAR_LOCK = 'D';
						MOVING = temp;
					}

				}

			}
			else {
				saveNameScore.score[saveNameScore.size - 1] = SCORE;
				writeFileScore(saveNameScore, (char*)nameFile1);
				if (temp == 'Y' || temp == 'y') {
					system("cls");
					SetColor(15, 4);
					for (int i = 66; i < 100; i++) {
						GotoXY(i, 16);
						cout << (char)205;
						GotoXY(i, 23);
						cout << (char)205;
					}
					for (int i = 16; i < 24; i++) {
						GotoXY(65, i);
						cout << (char)186;
						GotoXY(100, i);
						cout << (char)186;
					}
					GotoXY(65, 16); cout << (char)201;
					GotoXY(65, 23); cout << (char)200;
					GotoXY(100, 16); cout << (char)187;
					GotoXY(100, 23); cout << (char)188;
					SetColor(15, 0);
					char testTemp1[20];
					GotoXY(72, 18);
					cout << "Input your name player: \n";
					GotoXY(78, 20);
					cin.getline(testTemp1, 21);
					do {
						if (checkNameScore(saveNameScore, testTemp1)) {
							GotoXY(68, 18);
							cout << "Input your name player again: \n";
							GotoXY(78, 20);
							cout << "                ";
							GotoXY(78, 20);
							cin.getline(testTemp1, 21);
						}
					} while (checkNameScore(saveNameScore, testTemp1));
					saveNameScore.size++;
					saveNameScore.namePlay[saveNameScore.size - 1] = testTemp1;
					writeFileScore(saveNameScore, (char*)nameFile1);
					system("cls");
					StartGame();
				}
				else if (temp == 'B' || temp == 'b') {
					TerminateThread(handle_t1, 0);
					system("cls");
					menuGame();

				}

			}

		}
	}
}
