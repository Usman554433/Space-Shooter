/*Numair Imtiaz Cheema      l215343@lhr.nu.edu.pk
Syed Usman Ali              l215405@lhr.nu.edu.pk
Ahmed Naeem                 l211820@lhr.nu.edu.pk
Taieb Badar                 l217563@lhr.nu.edu.pk*/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
using namespace std;

//Function Declaration
void title();
void instruction();
void change(char& a, char& b);
void display(char[][20]);								//   displays output
void initialize(char[][20]);							//   starts the game at the beginning of every level
void generate(char[][20], int& slowgeneration);         //   generates asteroids at random columns
void move(char a[][20], int& index);                    //   used to control the spaceship
void fall(char a[][20]);                                //   makes the enemies fall towards the spaceship
void textcolor(int color);

int highscore, level, lives, score;
char continuity;

int main() {
	int choice = 1;
	while (choice == 1) {
		level = 1;
		score = 0;
		lives = 3;
		char a[22][20];
		initialize(a);
		int i = 0;
		int spaceship = 10;								 //   keeps track of the location of the spaceship
		ifstream obj("highscore.txt");

		if (obj)
			obj >> highscore;
		else
			highscore = 0;
		obj.close();
		title();
		instruction();
		display(a);
		int slowgeneration = 0;
		while (score < 50 && lives>0) {
			if (score >= level * 10) {
				system("CLS");
				cout << "Your Score is :" << score << endl;
				cout << "Congratulations! You are promoted to the next level. \a\n You are awarded an extra score for clearing a level" << endl << endl;
				level++;
				score++;
				system("pause");
				initialize(a);
				spaceship = 10;
			}
			display(a);
			i++;
			if (continuity == '1' && i % 5 == 0) {
				generate(a, slowgeneration);

				fall(a);

			}
			if (continuity != '1') {
				generate(a, slowgeneration);
				fall(a);
			}
			if (lives == 0) {
				if (score > highscore) {
					ofstream object;
					object.open("highscore.txt");
					object << score;
					object.close();
				}
				textcolor(4);
				cout << "	  |------------------------| \n";
				cout << "	  |-- G A M E   O V E R! --|\a";
				textcolor(7);
				cout<<"		-> E N T E R   1   T O  P L A Y   A G A I N " << endl; 
				textcolor(4);
				cout << "	  |------------------------|";
				cout << "               ";
				textcolor(7);
				cin >> choice;
				system("cls");
				
				continue;
				
			}
			move(a, spaceship);
		}
		if (score >= 50) {
			system("cls");
			if (score > highscore) {
				ofstream object;
				object.open("highscore.txt");
				object << score;
				object.close();
			}
			system("cls");
			cout << "	-- C O N G R A T U L A T I O N S!   Y O U    W O N. --  \n 	o P R E S S   1   T O  P L A Y   A G A I N" << endl;
			cin >> choice;
			system("cls");
			continue;
		}
	}
}
// TITLE PAGE

void title() {
	textcolor(2);
	cout << "					 ----------------------" << endl;
	cout << "					 | -- SPACE SHOOTER -- |" << endl;
	cout << "					 ----------------------" << endl << endl << endl;
	textcolor(7);
	cout << "					o Start Game " << endl;
	cout << "					o High Scores " << endl;
	cout << "					o Settings " << endl;
	cout << "					o Exit " << endl << endl << endl << endl << endl << "					";
	system("pause");
	system("CLS");
}
// INSTRUCTIONS PAGE
void instruction()
{
	char normalien = 223, highalien = 219;
	system("CLS");
	textcolor(9);
	cout << "						I N S T R U C T I O N S" << endl;
	cout << "				----------------------------------------------------------" << endl << endl;
	textcolor(7);
	cout << " o Use 'A' and 'D' to move your space ship Left and Right." << endl;
	cout << " o Use 'S' to shoot." << endl;
	cout << " o Press P to pause." << endl << endl;
	cout << " o Small Aliens:   ";
	textcolor(4);
	cout << normalien;
	textcolor(9);
	cout << "	gives 1pt each." << endl;
	textcolor(7);
	cout << " o Big Aliens:   ";
	textcolor(4);
	cout << highalien;
	textcolor(9);
	cout << "	gives 3pt each." << endl << endl << endl;
	cout << "						    S E T T I N G S" << endl;
	cout << "				----------------------------------------------------------" << endl << endl;
	textcolor(7);
	cout << " o 1) Continuous aliens";
	textcolor(4);
	cout << " (low performance)";
	textcolor(9);
	cout << "(low difficulty)";
	textcolor(7);
	cout << "\n\n o 2) ";
	textcolor(7);
	cout << "Aliens will only move when spaceship is moved ";
	textcolor(9);
	cout << " (high performance)";
	textcolor(4);
	cout << "(high difficulty)" << endl;
	textcolor(7);

	continuity = _getch();
	system("CLS");
}

//   Initializing Spaces in the playing area
void initialize(char a[][20]) {
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 20; j++) {
			a[i][j] = ' ';
		}
	}
	a[21][10] = 202;
}
void change(char& a, char& b) {
	char temp = a;
	a = b;
	b = temp;
}
void display(char a[][20]) {
	system("cls");
	char box = 177;
	for (int i = 0; i < 24; i++)
	{
		textcolor(4);
		for (int j = 0; j < 22; j++) {
			if (i == 22)
				textcolor(9);
			if (i == 0 || i == 23 || j == 0 || j == 21)
			{
				textcolor(7);
				cout << box << box;
			}
			else if (i != 22) {
				textcolor(4);
				cout << a[i - 1][j - 1] << " ";
			}
			else
				cout << a[i - 1][j - 1] << " ";
		}
		textcolor(7);
		if (i == 0 || i == 23 || i == 8)
			for (int i = 0; i < 75; i++)
				cout << box;
		if (i > 0 && i < 23 && i != 4 && i != 8 && i != 10 && i != 13 && i != 16 && i != 19)
		{
			for (int i = 0; i < 73; i++)
				cout << " ";
			cout << box << box;
		}
		char t = 203;
		if (i == 4)
			cout << "                       S P A C E   S H O O " << t << " E R                         " << box << box;
		if (i == 10)
			cout << "		Level : " << level << "						     " << box << box;
		if (i == 13)
			cout << "		Score : " << score << "						     " << box << box;
		if (i == 16)
			cout << "		Lives : " << lives << "						     " << box << box;
		//							CHANGE HIGH SCORE VARIABLE
		if (i == 19)
			cout << "		High score : " << highscore << "						     " << box << box;

		cout << endl;
	}
}
void generate(char a[][20], int& slowgeneration) {

	srand(time(0));
	if (slowgeneration % (7 - level) == 0) {
		int index = rand() % 21;
		a[0][index] = 254;
	}
	slowgeneration++;
	if (slowgeneration % 20 == 0) {
		int index = rand() % 21;
		a[0][index] = 178;
	}
}
void move(char a[][20], int& index) {
	char choice;
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 20; j++) {
			if (a[i][j] == 254) {
				change(a[i][j], a[i + 1][j]);
				display(a);
			}
		}
	}
	int c = 1;
	if (continuity == '1') {
		if (_kbhit()) {
			do {
				choice = _getch();

				if ((choice == 'd' || choice == 'D')) {
					if (index == 19)
						break;
					change(a[21][index], a[21][index + 1]);
					index++;
					c = 0;
					
				}
				if ((choice == 'a' || choice == 'A')) {
					if (index == 0)
						break;
					change(a[21][index], a[21][index - 1]);
					index--;
					c = 0;
				}
				if (choice == 's' || choice == 'S') {
					a[20][index] = 215;
					display(a);
					for (int i = 20; i > 0; i--) {
						if (a[i - 1][index] == (char)254) {
							display(a);
							score++;
							cout << '\a';
							a[i - 1][index] = ' ';
							a[i][index] = ' ';
							break;
						}
						if (a[i - 1][index] == (char)178) {
							display(a);
							score += 3;
							cout << '\a';
							a[i - 1][index] = ' ';
							a[i][index] = ' ';
							break;
						}

						change(a[i][index], a[i - 1][index]);
						if (i == 1) {
							display(a);
							a[i][index] = ' ';
							a[i - 1][index] = ' ';
						}

					}
					
				}
				if (choice != 'P' && choice != 'p')
					c = 0;
			} while (c);
		}
	}
	else {
		do {
			choice = _getch();

			if ((choice == 'd' || choice == 'D') && index != 19) {
				change(a[21][index], a[21][index + 1]);
				index++;
				c = 0;
			}
			if ((choice == 'a' || choice == 'A') && index != 0) {
				change(a[21][index], a[21][index - 1]);
				index--;
				c = 0;
			}
			if (choice == 's' || choice == 'S') {
				a[20][index] = 215;
				display(a);
				for (int i = 20; i > 0; i--) {
					if (a[i - 1][index] == (char)254) {
						display(a);
						score++;
						cout << '\a';
						a[i - 1][index] = ' ';
						a[i][index] = ' ';
						break;
					}
					if (a[i - 1][index] == (char)178) {
						display(a);
						score += 3;
						cout << '\a';
						a[i - 1][index] = ' ';
						a[i][index] = ' ';
						break;
					}
					change(a[i][index], a[i - 1][index]);
					if (i == 1) {
						display(a);
						a[i][index] = ' ';
						a[i - 1][index] = ' ';
					}

				}
				c = 0;
			}
		} while (c);
	}
}
void textcolor(int color) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
}

void fall(char a[][20]) {
	char b[22][20];
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 20; j++) {
			b[i][j] = a[i][j];
		}
	}
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 20; j++) {
			if (b[i][j] == (char)254 && (i + (level / 3) + 1) >= 21 || b[i][j] == (char)178 && (i + (level / 3) + 1) >= 21) {
				a[i][j] = ' ';
				lives--;
				cout << "\a";
				system("Color 04");
				display(a);
				if (lives == 0)
					return;
			}
			if (a[i][j] == (char)254 && b[i][j] == (char)254) {
				change(a[i][j], a[i + (level / 3) + 1][j]);

			}
			if (a[i][j] == (char)178 && b[i][j] == (char)178 && a[i + (level / 3) + 1][j] == ' ') {
				change(a[i][j], a[i + (level / 3) + 1][j]);
			}
		}
	}
}