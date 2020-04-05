#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<time.h>

#define HIGH 23
#define WIDTH 100
#define MAX_SNAKE_LENGTH (HIGH-2)*(WIDTH-2)

int sLength = 1;
bool control_fail = false;
bool control_first_set = false;//setMap için kontrol butonu
								//ilk setlemede duvarlarda setlenir daha sonrakilerde duvarlar tekrar setlenilmemesi için 
bool control_feed = true;		//harita üzerinde yem var mý? 
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
class GameMotor:public AuxiliaryFunctions {
	public:
		void mainMenu() {
			/*gotoXY((WIDTH / 2) - 10, (HIGH / 2) -5);
			for (int i = 0; i < 20; i++) cout << char(178);

			gotoXY((WIDTH / 2) - 10, (HIGH / 2) - 2);
			cout <<endl<< "     SNAKE GAME     "<<endl;
			gotoXY((WIDTH / 2) - 10, (HIGH / 2) + 5);
			for (int i = 0; i < 20; i++) cout << char(178);*/
			for (int i = 0; i < 50; i++) cout << char(178);
			cout << endl << endl << endl;
			//cout << " " * 17 + "SNAKE GAME" + " " * 17;
			for (int i = 0; i < 50; i++) cout << char(178);
			
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
		
		void setMap() {
			//if (!control_first_set) {
			for (int i = 0; i < HIGH; i++) {
				for (int j = 0; j < WIDTH; j++) {
					if (i == 0 || i == HIGH - 1 || j == 0 || j == WIDTH - 1) map[i][j] = wall;
					else map[i][j] = char(255);
				}
			}
			//control_first_set = true;
			//}
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
		void clearMap() {//HIGH-1 WIDTH-1
			for (int i = 1; i < HIGH; i++) {
				for (int j = 1 ; j < WIDTH; j++) {
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
			//if (control_feed) {
			do {
				feedx = (rand() % WIDTH) + 1;
				feedy = (rand() % HIGH) + 1;
				if (feedx >= WIDTH || feedy >= HIGH) continue;
			} while (map[feedy][feedx] == snake && map[feedy][feedx] == wall);
			gotoXY(5, HIGH+1);
			//cout << "X : " << feedx<<"	"<<"Y : "<<feedy<<endl;

			//}
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
			/*snakeTail[0].x = x;
			snakeTail[0].y = y;
			snakeTail[0].direction = d;*/
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
			//switch (key) {
			//case 'w':
			//case 'W':
			//	if (wallControl(snakeTail[0].x, snakeTail[0].y - 1)) y--;//snakeTail[0].y--;
			//	else y = HIGH - 1;//snakeTail[0].y = HIGH - 1;
			//	d= d_Up;//snakeTail[0].direction = d_Up;
			//	break;
			//case 's':
			//case 'S':
			//	if (wallControl(snakeTail[0].x, snakeTail[0].y + 1)) y++;//snakeTail[0].y++;
			//	else y = 1; //snakeTail[0].y = 1;
			//	d = d_Down; //snakeTail[0].direction = d_Down;
			//	
			//	break;
			//case 'a':
			//case 'A':
			//	if (wallControl(snakeTail[0].x - 1, snakeTail[0].y)) x--;// snakeTail[0].x--;
			//	else x = WIDTH - 1; //snakeTail[0].x = WIDTH - 1;
			//	d = d_Left; //snakeTail[0].direction = d_Left;
			//	break;
			//case 'd':
			//case 'D':
			//	if (wallControl(snakeTail[0].x + 1, snakeTail[0].y)) x++;// snakeTail[0].x++;
			//	else x = 1; //snakeTail[0].x = 1;
			//	d = d_Right; //snakeTail[0].direction = d_Right;
			//	break;
			//}
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
			//add();
			isCaugth();
			//animationTail(x, y, d);
			animationTail();
		}
		void moveSnake() {
			listenKey(keys);
			int x = snakeTail[0].x;
			int y = snakeTail[0].y;
			Direction d = snakeTail[0].direction;
			
			//if (keys['W'] != 0) {
			//	if (!wallControl(snakeTail[0].x, snakeTail[0].y - 1)) control_fail = true;
			//	 y--;//snakeTail[0].y--;
			//	
			//	d = d_Up;//snakeTail[0].direction = d_Up;
			//}
			//else if (keys['S'] != 0) {
			//	if (!wallControl(snakeTail[0].x, snakeTail[0].y + 1)) control_fail = true;
			//	y++;//snakeTail[0].y++;
			//	d = d_Down; //snakeTail[0].direction = d_Down;
			//}
			//if (keys['A'] != 0) {
			//	if (!wallControl(snakeTail[0].x - 1, snakeTail[0].y)) control_fail = true;
			//	x--;// snakeTail[0].x--;
			//	d = d_Left; //snakeTail[0].direction = d_Left;
			//}
			//if (keys['D'] != 0) {
			//	if (!wallControl(snakeTail[0].x + 1, snakeTail[0].y)) control_fail = true;
			//	x++;// snakeTail[0].x++; 
			//	d = d_Right; //snakeTail[0].direction = d_Right;
			//}

			if (keys['W'] != 0) {
				snakeTail[0].y--;
				
				snakeTail[0].direction = d_Up;
			}
			else if (keys['S'] != 0) {
				snakeTail[0].y++;
				snakeTail[0].direction = d_Down;
			}
			if (keys['A'] != 0) {
				snakeTail[0].x--;
				snakeTail[0].direction = d_Left;
			}
			if (keys['D'] != 0) {
				snakeTail[0].x++; 
				snakeTail[0].direction = d_Right;
			}
			isCaugth();
			//animationTail(x, y, d);
		}
		void isCaugth() {
			if (snakeTail[0].x == feedx && snakeTail[0].y == feedy) {
				//control_feed = true;
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
			//moveSnake();
			//animationTail();
		}
		/*system("CLS");
		cout << endl << endl << " GAME OVER ";
		char a = _getch();*/
	}
};

int main() {
	
	SnakeGame game;
	game.play();
	

	return 0;
}

