#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<time.h>

#define HIGH 23
#define WIDTH 100
#define MAX_SNAKE_LENGTH (HIGH-2)*(WIDTH-2)

using namespace std;

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

class AuxiliaryFunctions {//yardimci fonksiyonlar
	public:
		char keys[256];

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
		void listenKey(char keys[]) {
			for (int i = 0; i < 256; i++) keys[i] = char(GetAsyncKeyState(i) >> 8);
		}
};
class SnakeGame : public AuxiliaryFunctions {
	private:
		char snake = char(219); //yýlan
		char wall = char(219); //duvar
		char feed = '@'; //yem
		int feedx=1, feedy=1;
		char map[HIGH][WIDTH];
		int sy = HIGH / 2, sx = WIDTH / 2;
		int sLength = 1;
		
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
		bool wallControl(int x,int y) {
			if (map[y][x] != wall) return true;
			else if (map[y][x] = wall)return false;
		}
		void produceFeedCoord() {
			srand(time(0));
			do {
				feedx = (rand() % WIDTH) + 1;
				feedy = (rand() % HIGH) + 1;
				if (feedx > WIDTH || feedy > HIGH) continue;
			} while (map[feedy][feedx] == snake && map[feedy][feedx] == wall);
		}
		void createSnake() {
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
		void add() {
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
			int x = snakeTail[0].x;
			int y = snakeTail[0].y;
			Direction d = snakeTail[0].direction;
			char key = _getch();
			
			switch (key) {
			case 'w':
			case 'W':
				snakeTail[0].y--;
				snakeTail[0].direction = d_Up;
				break;
			case 's':
			case 'S':
				snakeTail[0].y++;
				snakeTail[0].direction = d_Down;
				break;
			case 'a':
			case 'A':
				snakeTail[0].x--;
				snakeTail[0].direction = d_Left;
				break;
			case 'd':
			case 'D':
				snakeTail[0].x++;
				snakeTail[0].direction = d_Right;
				break;
			}
			isCaugth();
			animationTail();
		}
		void isCaugth() {
			if (snakeTail[0].x == feedx && snakeTail[0].y == feedy) {
				add();
				produceFeedCoord();	
			}
		}
		
public:
	void play() {
		hideCursor();
		createSnake();
		produceFeedCoord();
		while (true) {
			gotoXY(0, 0);
			clearMap();
			setMap();
			drawMap();
			move();
		}
	}
};

int main() {
	
	SnakeGame game;
	game.play();
	
	return 0;
}
