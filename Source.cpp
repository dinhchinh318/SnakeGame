#include "mylib.h"

int idxObstaclelv2 = 0;
int idxObstaclelv3 = 0;
int idxObstaclelv4 = 0;
int LEVEL = 1;
int SCORE = 0;
saveSnake luusnake;
char dname[100];
saveNameFile saveName;
saveScore saveNameScore;
int arrTemp[MAX];
string arrNameTemp[MAX];


//Global variables
POINT snake[20]; //snake
POINT food[50]; // food
POINT ObstacleXlv2[500];
POINT ObstacleXlv3[500];
POINT ObstacleXlv4[500];
POINT obstaclelv3[2];

int checkObstacle;
int MovingObstacle;
int CHAR_LOCK;//used to determine the direction my snake cannot move (At amoment, there is one direction my snake cannot move to)
int MOVING;//used to determine the direction my snake moves (At a moment, thereare three directions my snake can move)
double SPEED;// Standing for level, the higher the level, the quicker the speed
int HEIGH_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
int FOOD_INDEX; // current food-index
int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size may 10
int STATE; // State of snake: dead or alive

void main() {

	ResizeConsoleWindow(150, 60);
	CenterConsoleWindow();
	ShowConsoleCursor(false);
	fixConsoleWindow();
	backgroundSound();
	introGame();
	menuGame();
}