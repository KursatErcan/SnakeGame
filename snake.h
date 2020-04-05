#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<time.h>

#define HIGH 23
#define WIDTH 100
#define MAX_SNAKE_LENGTH (HIGH-2)*(WIDTH-2)

using namespace std;

int sLength = 0;
bool game_over = false;

enum Direction
{
	d_Left = 1,
	d_Right = 2,
	d_Up = 3,
	d_Down = 4
};
struct Snake {
	int x;
	int y;
	Direction direction;
}snakeTail[MAX_SNAKE_LENGTH];

void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void hideCursor()      // ekranda surekli cikan kursoru kapatir  
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO    cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

class SnakeGame {
	private:
		char snake, wall, feed;
		int feedx, feedy, sy, sx;
		int score;
		char key;
		char map[HIGH][WIDTH];

		void setup() {
			snake = char(219); //yılan
			wall = char(219); //duvar
			feed = '@'; //yem
			feedx = 1, feedy = 1;
			sy = HIGH / 2, sx = WIDTH / 2;
			key;
			score = 0;
		}
		void setMap() {
			for (int i = 0; i < HIGH; i++) {
				for (int j = 0; j < WIDTH; j++) {
					if (i == 0 || i == HIGH - 1 || j == 0 || j == WIDTH - 1) map[i][j] = wall;
					else map[i][j] = char(255);
				}
			}
			for (int i = 0; i < sLength; i++) { //yýlaný sahneye yerleþtir
				map[snakeTail[i].y][snakeTail[i].x] = snake;
			}
			map[feedy][feedx] = feed; //yemi sahneye yerleþtir
		}
		void drawMap() {
			gotoXY(0, 0);
			clearMap();
			setMap();
			for (int i = 0; i < HIGH; i++) {
				for (int j = 0; j < WIDTH; j++) {
					cout<<map[i][j] ;
				}
				cout << endl;
			}
		}
		void clearMap() {
			for (int i = 0; i < HIGH; i++) {
				for (int j = 0; j < WIDTH; j++) {
					map[i][j]= char(255);
				}
			}
		}
		void hitControl() {
			if (snakeTail[0].y != 0 && snakeTail[0].y != HIGH - 1 && snakeTail[0].x != 0 && snakeTail[0].x != WIDTH - 1) game_over = false;
			else true;
			if (!game_over) {
			for (int i = 2; i < sLength; i++) {
				if (snakeTail[0].y == snakeTail[i].y && snakeTail[0].x == snakeTail[i].x) {
					game_over = true;
					break;
					}
				}
			}
		}
		void produceFeedCoord() {
			srand(time(0));
			while (true) {
				feedx = ((rand() + WIDTH) % (WIDTH - 1)) + 1;
				feedy = ((rand() + HIGH) % (HIGH - 1)) + 1;
				if (map[feedy][feedx] != snake && (feedx<WIDTH-1 || feedy<HIGH-1)) break;
			}
		}
		void createSnake() {
			sLength = 1;
			snakeTail[0].x = sx;
			snakeTail[0].y = sy;
			snakeTail[0].direction = d_Up;
		}
		void animationTail() {
			for (int i = sLength - 1; i > 0; i--) {
				snakeTail[i].x = snakeTail[i - 1].x;
				snakeTail[i].y = snakeTail[i - 1].y;
				snakeTail[i].direction = snakeTail[i - 1].direction;
			}
		}
		void addTail() {
			sLength++;
			snakeTail[sLength - 1].x = snakeTail[sLength - 2].x;
			snakeTail[sLength - 1].y = snakeTail[sLength - 2].y;
			snakeTail[sLength - 1].direction = snakeTail[sLength - 2].direction;
			switch (snakeTail[sLength - 2].direction) {
				case d_Up:
					snakeTail[sLength - 1].y += 1;
					break;
				case d_Down:
					snakeTail[sLength - 1].y -= 1;
					break;
				case d_Right:
					snakeTail[sLength - 1].x -= 1;
					break;
				case d_Left:
					snakeTail[sLength - 1].x += 1;
					break;
			}
		}
		void move() {
			if (_kbhit()) {
				key = _getch();
			}
			switch (key) {
			case 'w':
			case 'W':
				snakeTail[0].y--;
				snakeTail[0].direction = d_Up;
				key = 'w';
				break;
			case 's':
			case 'S':
				snakeTail[0].y++;
				snakeTail[0].direction = d_Down;
				key = 's';
				break;
			case 'a':
			case 'A':
				snakeTail[0].x--;
				snakeTail[0].direction = d_Left;
				key = 'a';
				break;
			case 'd':
			case 'D':
				snakeTail[0].x++;
				snakeTail[0].direction = d_Right;
				key = 'd';
				break;
			default:
				switch (snakeTail[0].direction) {
				case d_Up:
					snakeTail[0].y -= 1;
					break;
				case d_Down:
					snakeTail[0].y += 1;
					break;
				case d_Right:
					snakeTail[0].x += 1;
					break;
				case d_Left:
					snakeTail[0].x -= 1;
					break;
				}
				break;
			}
			if (snakeTail[0].x >= WIDTH) snakeTail[0].x = 0; else if (snakeTail[0].x < 0) snakeTail[0].x = WIDTH - 1;
			if (snakeTail[0].y >= HIGH) snakeTail[0].y = 0; else if (snakeTail[0].y < 0) snakeTail[0].y = HIGH - 1;
			hitControl();
			isCaugth();
			animationTail();
		}
		void isCaugth() {
			if (snakeTail[0].x == feedx && snakeTail[0].y == feedy) {
				addTail();
				produceFeedCoord();	
			}
		}
		
public:
	void play() {
		hideCursor();
		setup();
		createSnake();
		produceFeedCoord();
		while (!game_over) {
			Sleep(25);
			drawMap();
			move();
		}
		system("CLS");
		cout << endl << endl << " GAME OVER ";
		char a = _getch();
	}
};


