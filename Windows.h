#include<iostream>

using namespace std;


class Window{

public:
	void mainMenu() {
		int selection = 1;
		char key=NULL;
		
		while (key != char(13)) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
			gotoXY(WIDTH / 2, HIGH / 2 - 6);
			cout << "   w   ";
			gotoXY(WIDTH / 2, HIGH / 2 - 3);
			cout << " Start ";
			gotoXY(WIDTH / 2, HIGH / 2 - 2);
			cout << "Options";
			gotoXY(WIDTH / 2, HIGH / 2 - 1);
			cout << " Quit  ";
			
			gotoXY(WIDTH / 2, HIGH / 2 + 2);
			cout << "   s   ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
			gotoXY(WIDTH / 2 -4, HIGH / 2 - 3 + selection);
			cout << "->";
			gotoXY(WIDTH / 2 +8, HIGH / 2 - 3 + selection);
			cout <<"<-";

			key = _getch();
			if (key == 'w'&& selection>0) selection--;
			else if (key == 's'&& selection<2) selection++;
			
			system("cls");
		}

		switch (selection) {
		case 0:
			SnakeGame game;
			game.play();
			break;
		case 1:

			break;
		case 2:
			game_over = true;
			break;
		}
	}
};