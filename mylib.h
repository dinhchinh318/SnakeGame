#ifndef _MY_PROJECT_
#define _MY_PROJECT_

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <thread>
#include <string>
#include <vector>
#include <mmsystem.h>
#include <dsound.h>
#include <fstream>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#define nameFile "nameFileSave.txt"
#define nameFile1 "nameFileScore.txt"

#define MAX 100

//Constants
#define MAX_SIZE_SNAKE 20
#define MAX_SIZE_FOOD 4
#define MAX_SPEED 5

using namespace std;


struct saveSnake {
	int snakeSize;
	POINT SaveSnake[50];
	int level;
	POINT food;
	int foodIndex;
	int luuScore;
	int luuCHAR_LOCK;
	int luuMOVING;
	POINT obstacle[2];
};

struct saveNameFile {
	string name[MAX];
	int size;
};

struct saveScore {
	string namePlay[MAX];
	int score[MAX];
	int size;
};


extern int idxObstaclelv2;
extern int idxObstaclelv3;
extern int idxObstaclelv4;
extern int LEVEL;
extern int SCORE;
extern saveSnake luusnake;
extern char dname[100];
extern saveNameFile saveName;
extern saveScore saveNameScore;
extern int arrTemp[MAX];
extern string arrNameTemp[MAX];

//Global variables
extern POINT snake[20]; //snake
extern POINT food[50]; // food
extern POINT ObstacleXlv2[500];
extern POINT ObstacleXlv3[500];
extern POINT ObstacleXlv4[500];
extern POINT obstaclelv3[2];

extern int checkObstacle;
extern int MovingObstacle;
extern int CHAR_LOCK;//used to determine the direction my snake cannot move (At amoment, there is one direction my snake cannot move to)
extern int MOVING;//used to determine the direction my snake moves (At a moment, thereare three directions my snake can move)
extern double SPEED;// Standing for level, the higher the level, the quicker the speed
extern int HEIGH_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
extern int FOOD_INDEX; // current food-index
extern int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size may 10
extern int STATE; // State of snake: dead or alive


void GotoXY(int x, int y);

void fixConsoleWindow();
void CenterConsoleWindow();
void ResizeConsoleWindow(int width, int height);
void ShowConsoleCursor(bool showFlag);
void maximizeConsoleWindow();
void hideScrollBar();
void SetColor(int backgound_color, int text_color);


void printMyFile(const char* fileName);
void writeFileScore(saveScore& saveNameScore, char dname[]);
void readFileScore(saveScore& saveNameScore, char dname[]);
void writeFileName(saveNameFile& saveName, char dname[]);
void readFileName(saveNameFile& saveName, char dname[]);
void ghifile(saveSnake luusnake, char dname[]);
bool hasInvalidChars(const char* filename);
bool isValidFileName(const char* filename);
bool checkName(saveNameFile& saveName, const char* text);
bool checkNameScore(saveScore& saveNameScore, const char* text);
void docfile(saveSnake& luusnake, char dname[]);

void introGame();
void playGame(int x);
void help();
void about();
void loadgame();
void Score();
void Setting();
void menuGame();


bool IsValid(int x, int y);
void GenerateFood();
void ResetData();

void DrawBoard(int x, int y, int width, int height);
void DrawMaplv2();
void DrawMaplv3();
void DrawObstaclelv3(const char* str);
void DrawMaplv4();
bool checkFoodlv2(int x, int y);
bool checkFoodlv3(int x, int y);
bool checkFoodlv4(int x, int y);
bool CheckCollisionWithObstaclelv2();
bool CheckCollisionWithObstaclelv3_Wall();
bool CheckCollisionWithObstaclelv3();
bool CheckCollisionWithObstaclelv4();
void ResetObstaclelv2();
void ResetObstaclelv3();
void ResetObstaclelv4();

void StartGame();
void StartGameLoad();
void ExitGame(HANDLE t);
void PauseGame(HANDLE t);
void DrawPortal();
void DrawSnakeAndFood(const char* str);
void ChangeLevel(int level);
void Eat();
void ProcessDead();
void DrawSnakeAndFood1(); //Draw snake's body by studentsID
bool CheckCollision(); //Check if snake collides its body

void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();
bool GameOver();
void Move1();
void Move2();
void Move3();
void Move4();
void settingObstacle();
void setThread();
void ThreadFunc();

void DrawSnake1(const char* str);
void DrawSnake();
void BlinkSnake(int blinkCount, int delayMilliseconds);

void backgroundSound();
void StopBackgroundMusic();
void PlayEatSound();
void PlayDeadSound();
void PlayWinSound();
void PlayButtonSound();

#endif // !_MY_PROJECT_


