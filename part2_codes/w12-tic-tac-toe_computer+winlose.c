#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_STR 50

int board[3][3] = { 0 };
int ver, entry = 0;

int ordering(void);
int NotGameOver(void);
int charcheck(char);
int pos_read_op(int);
int getmaxcolumns(void);
int set_print(int);
void block_print(COORD);
void point_print(int, int, int);
void board_print(int);
void set_seed(void);
int rand_num(void);
void computer_turn(void);
void stdtext(void);
void gotoXY(int, int);
COORD cur_cur(void);
void end_set(void);

void main(void) {
	int max_columns;

	ver = ordering();

	for (int i = 0; NotGameOver(); i++) {
		system("cls");
		max_columns = set_print(ver);
		board_print(max_columns);

		if ((i + ver) % 2) {
			Sleep(1000);
			stdtext();
			computer_turn();
		}
		else pos_read_op(max_columns);
	} 

	board_print(set_print(ver));
	end_set();
}

int ordering(void) {
	int comm;

	gotoXY(0, 0);
	puts("### Tic-Tac-Toe ###");
	puts("1 : Play first (X)");
	puts("2 : Play second (O)");
	puts("3 : Exit");
	printf("Enter command : ");

	scanf("%d", &comm);

	switch (comm) {
	case 1:
		return (0);
		break;
	case 2:
		return (1);
		break;
	case 3:
		exit(0);
		break;
	default:
		system("cls");
		return (ordering());
		break;
	}
}

int NotGameOver(void) {
	int n;

	for (int i = 0; i < 3; i++) {
		n = board[i][0];
		if (n != 0 && board[i][1] == n && board[i][2] == n) {
			gotoXY(55, 26);

			if (n == ver + 1) printf("Your win!!");
			else printf("Your lose..");

			return 0;
		}

		n = board[0][i];
		if (n != 0 && board[1][i] == n && board[2][i] == n) {
			gotoXY(55, 26);

			if (n == ver + 1) printf("Your win!!");
			else printf("Your lose..");

			return 0;
		}
	}

	for (int k = 0; k < 2; k++) {
		n = board[0 + 2 * k][0];
		if (n != 0 && board[1][1] == n && board[2 - 2 * k][2] == n) {
			if (n == ver + 1) {
				gotoXY(55, 26);
				printf("Your win!!");
			}
			else {
				gotoXY(55, 26);
				printf("Your lose..");
			}

			return 0;
		}
	}


	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (board[i][j]==0)
				return 1;
	

	gotoXY(58, 26);
	printf("DRAW");
	return 0;
}

int charcheck(char c) {
	int a = c-'0';
	if (isdigit(c) && a != 0 && board[(a - 1) / 3][(a - 1) % 3] == 0)
		return 1;

	return 0;
}

int pos_read_op(int max_columns) {
	const char* str = "Enter the place where you want to check : "; 
	char buf[MAX_STR] = "\0";
	int a;

	stdtext();

	gotoXY((max_columns-strlen(str)-1)/2, 24);
	printf("%s", str);

	gets(buf);
	
	if (strlen(buf) == 1 && charcheck(*buf)) {
		a = atoi(buf) - 1;
		board[a / 3][a % 3] = 1 + ver;
		gotoXY(0, 0);
		printf("%d", entry);
	}
	else { 
		system("cls");
		board_print(set_print(ver));
		return (pos_read_op(max_columns)); 
	}

	return 0;
}

int getmaxcolumns(void) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	return (columns);
}

int set_print(int ver) {
	int max_columns = getmaxcolumns();

	const char* str1 = "### Tic-Tac-Toe ###", * str2 = "Player 1: Human, Player 2: Computer",
		*str3= "Player 1: Computer, Player 2: Human";

	stdtext();
	
	gotoXY((max_columns - strlen(str1)) / 2, 2);
	printf("%s", str1);

	switch (ver) {
	case 0:
		gotoXY((max_columns - strlen(str2)) / 2, 5);
		printf("%s", str2);
		break;
	case 1:
		gotoXY((max_columns - strlen(str3)) / 2, 5);
		printf("%s", str3);
		break;
	}
	

	return (max_columns);
}

char toOX(int n) {
	char answer;
	switch (n) {
	case 0:
		answer = ' ';
		break;
	case 1:
		answer = 'X';
		break;
	case 2:
		answer = 'O';
		break;
	}

	return (answer);
}

void set_color(int n) {
	switch (n % 2) {
	case 0:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		break;
	case 1:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		break;
	}
}
void block_print(COORD cur) {
	int x_p = cur.X, y_p = cur.Y, n = 5;

	while (n-- > 0) {
		gotoXY(cur.X, cur.Y);
		printf("     ");
		cur.X = x_p; cur.Y = ++y_p;
	}
}

void point_print(int i, int j, int max_columns) {
	gotoXY((max_columns - 15) / 2 + 5 * j + 2, 10 + 5 * i);
	printf("%c", toOX(board[i][j]));
}

void board_print(int max_columns) {
	COORD cur = { 0, 0 };
	for (int i = 0; i < 3; i++) {
		cur.Y = 8 + 5 * i;
		for (int j = 0; j < 3; j++) {
			set_color(i+j);
			cur.X = (max_columns - 15) / 2 + 5 * j;
			block_print(cur);
			point_print(i, j, max_columns);
		}
	}
}

void set_seed(void) {
	srand((unsigned)time(NULL));
}

int rand_num(void) {
	return (rand() % 9 + 0);
}

void computer_turn(void) {
	set_seed();

	int n;
	do {
		n=rand_num();
	} while (board[n / 3][n % 3] != 0);

	board[n / 3][n % 3] = 2 - ver;
}

void stdtext(void) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 << 4) + 15);
}

void gotoXY(int x, int y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

COORD cur_cur(void) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	COORD answer_coor = { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y };

	return answer_coor;
}

void end_set(void) {
	stdtext();
	gotoXY(0, 28);
}