#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STR 50

int board[3][3] = { 0 };

int NotGameOver(void);
int charcheck(char);
int read_op(int);
int getmaxcolumns(void);
int set_print(void);
void block_print(COORD);
void point_print(int, int, int);
void board_print(int);
void stdtext(void);
void gotoXY(int, int);
void end_set(void);

void main(void) {
	int max_columns;

	while (NotGameOver()) {
		system("cls");
		gotoXY(0, 0);
		max_columns = set_print();
		board_print(max_columns);
		read_op(max_columns);
	} 

	board_print(set_print());
	end_set();
}

int NotGameOver(void) {
	int answer = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (board[i][j]==0)
				return 1;
	return (answer);
}

int charcheck(char c) {
	if (isdigit(c) && c != '0')
		return 1;

	return 0;
}

int read_op(int max_columns) {
	const char* str = "Enter the place where you want to check : "; 
	char buf[MAX_STR] = "\0";
	int a;

	stdtext();
	gotoXY((max_columns-strlen(str)-1)/2, 24);
	printf("%s", str);
	fgets(buf, 2, stdin);

	if (strlen(buf) == 1 && charcheck(*buf)) {
		a = atoi(buf) - 1;
		board[a / 3][a % 3] = 1;
	}
	else { 
		gotoXY((max_columns - strlen(str) - 1) / 2 + strlen(str), 24);
		printf(" ");
		return (read_op(max_columns)); 
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

int set_print(void) {
	int max_columns = getmaxcolumns();

	const char* str1 = "### Tic-Tac-Toe ###", * str2 = "Player 1: Human, Player 2: Computer";

	stdtext();
	
	gotoXY((max_columns - strlen(str1)) / 2, 2);
	printf("%s", str1);

	gotoXY((max_columns - strlen(str2)) / 2, 5);
	printf("%s", str2);

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

void stdtext(void) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 << 4) + 15);
}

void gotoXY(int x, int y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void end_set(void) {
	stdtext();
	gotoXY(0, 28);
}