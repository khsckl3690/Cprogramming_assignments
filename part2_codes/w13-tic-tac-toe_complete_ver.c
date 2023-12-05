#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_STR 50

int board[3][3] = { 0 };
int heur[9][2] = { 0 };
int ver, WorL, com_mode = 0;

int com_pick(int);
int ordering(void);
const char* com_level(void);
int NotGameOver(void);
int charcheck(char);
int pos_read_op(int);
int getmaxcolumns(void);
void set_print(int);
void block_print(COORD);
void point_print(int, int, int);
void board_print(int);
void set_seed(void);
int rand_num(int);
int dumber_com(void);
int dumb_com(void);
int smart_com(void);
void heur_update(void);
void heur_init(void);
void row_update(int);
void col_update(int);
void bsl_update(int);
void sla_update(int);
int win_case(void);
int lose_case(void);
int even_count(void);
int odd_count(void);
void entry_add(int, int);
int squ(int);
int Max_Entry(int A[9][2], int);
void stdtext(void);
void gotoXY(int, int);
COORD cur_cur(void);
void end_set(int);


void main(void) {
	int max_columns = getmaxcolumns(), choice;

	set_seed();

	ver = ordering();
	heur_update();

	if (ver == 2) {
		int rand_com = 1;

		for (int i = 0; NotGameOver(); i++) {
			system("cls");
			set_print(max_columns);
			board_print(max_columns);

			Sleep(1000);
			stdtext();

			if (i % 2) {
				ver = 0;
				choice = com_pick(rand_com);
			}
			else {
				ver = 1;
				choice = com_pick(com_mode);
			}

			board[choice / 3][choice % 3] = 2 - ver;

			heur_update();
			ver = 2;
		}
	}
	else {
		for (int i = 0; NotGameOver(); i++) {
			system("cls");
			set_print(max_columns);
			board_print(max_columns);

			if ((i + ver) % 2) {
				Sleep(1000);
				stdtext();
				choice = com_pick(com_mode);
				board[choice / 3][choice % 3] = 2 - ver;
			}
			else choice = pos_read_op(max_columns);

			heur_update();
		}
	}

	set_print(max_columns);
	board_print(max_columns);
	end_set(max_columns);
}

int com_pick(int n) {
	switch (n) {
	case 0:
		return (dumber_com());
	case 1:
		return (dumb_com());
	case 2:
		return (smart_com());
	default:
		return (com_mode);
	}
}

int ordering(void) {
	int comm;

	gotoXY(0, 0);
	puts("### Tic-Tac-Toe ###");
	puts("1 : Play first (X)");
	puts("2 : Play second (O)");
	puts("3 : Computer vs Computer");
	printf("4 : Select AI (current: %s)\n", com_level());
	puts("0 : Exit");
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
		return (2);
		break;
	case 4:
		system("cls");
		puts("0 : dumber");
		puts("1 : dumb");
		puts("2 : smart");
		printf("Enter command: ");

		scanf("%d", &comm);
		switch (comm) {
		case 0:
			com_mode = 0;
			break;
		case 1:
			com_mode = 1;
			break;
		case 2:
			com_mode = 2;
			break;
		}

		system("cls");
		return (ordering());
		break;
	case 0:
		exit(0);
		break;
	default:
		system("cls");
		return (ordering());
		break;
	}
}

const char* com_level(void) {
	char* str = (char*)malloc(sizeof(char) * MAX_STR);

	switch (com_mode) {
	case 0:
		strcpy(str, "dumber");
		break;
	case 1:
		strcpy(str, "dumb");
		break;
	case 2:
		strcpy(str, "smart");
		break;
	}

	return ((const char*)str);
}

int NotGameOver(void) {
	int n;

	for (int i = 0; i < 3; i++) {
		n = board[i][0];
		if (n != 0 && board[i][1] == n && board[i][2] == n) {
			if (n == ver + 1) WorL = 1;
			else WorL = -1;

			return 0;
		}

		n = board[0][i];
		if (n != 0 && board[1][i] == n && board[2][i] == n) {
			if (n == ver + 1) WorL = 1;
			else WorL = -1;

			return 0;
		}
	}

	for (int k = 0; k < 2; k++) {
		n = board[0 + 2 * k][0];
		if (n != 0 && board[1][1] == n && board[2 - 2 * k][2] == n) {
			if (n == ver + 1) WorL = 1;
			else WorL = -1;

			return 0;
		}
	}


	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (board[i][j]==0)
				return 1;
	
	WorL = 0;
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

	gotoXY((max_columns - (int)strlen(str)-1)/2, 24);
	printf("%s", str);

	fgets(buf, MAX_STR, stdin); buf[strcspn((const char*)buf, "\n")] = '\0';
	
	if (strlen(buf) == 1 && charcheck(*buf)) {
		a = atoi(buf) - 1;
		board[a / 3][a % 3] = 1 + ver;
	}
	else { 
		system("cls");
		set_print(max_columns);
		board_print(max_columns);
		return (pos_read_op(max_columns)); 
	}

	return (a);
}

int getmaxcolumns(void) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	return (columns);
}

void set_print(int max_columns) {
	const char* str1 = "### Tic-Tac-Toe ###", * str2 = "Player 1: Human, Player 2: Computer",
		* str3= "Player 1: Computer, Player 2: Human", * str4 = "Player 1: Computer(You chose), Player 2: Computer";

	stdtext();
	
	gotoXY((max_columns - (int)strlen(str1)) / 2, 2);
	printf("%s", str1);

	switch (ver) {
	case 0:
		gotoXY((max_columns - (int)strlen(str2)) / 2, 5);
		printf("%s", str2);
		break;
	case 1:
		gotoXY((max_columns - (int)strlen(str3)) / 2, 5);
		printf("%s", str3);
		break;
	case 2:
		gotoXY((max_columns - (int)strlen(str4)) / 2, 5);
		printf("%s", str4);
		break;
	}
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

//it returns a random integer from 0 to the number which is given as a parameter
int rand_num(int num) {
	return (rand() % num + 0);
}

int dumber_com(void) {
	int n;
	do {
		n = rand_num(9);
	} while (board[n / 3][n % 3] != 0);

	return (n);
}

int dumb_com(void) {
	int win = win_case();

	if (win == 9) {
		int lose = lose_case();

		if (lose == 9) {
			if (board[1][1]) {
				int even = even_count();

				if (even == 0) {
					int odd = odd_count();

					return (odd);

				}
				else return (even);
		
			}
			else return (4);
	
		}
		else return (lose);
	
	}
	else return (win);

}

int smart_com(void) {
	int win = win_case();

	if (win == 9) {
		int lose = lose_case();

		if (lose == 9) {
			return (Max_Entry(heur, 1 - ver));
		}
		else return (lose);

	}
	else return (win);

}

void heur_update(void) {
	heur_init();

	for (int i = 0; i < 9; i++) {
		row_update(i);
		col_update(i);
	}

	for (int i = 0; i < 3; i++) {
		bsl_update(4 * i);
		sla_update(2 + 2 * i);
	}
}

void heur_init(void) {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 2; j++)
			heur[i][j] = 0;
}

void row_update(int p) {
	int answer;

	for (int i = 0; i < 3; i++) {
		answer = (p + i) % 9;
		entry_add(answer, board[p / 3][p % 3]);
	}
}

void col_update(int p) {
	int answer;

	for (int i = 0; i < 3; i++) {
		answer = (p + 3 * i) % 9;
		entry_add(answer, board[p / 3][p % 3]);
	}
}

void bsl_update(int p) {
	int answer;

	for (int i = 0; i < 3; i++) {
		answer = 4 * i;
		entry_add(answer, board[p / 3][p % 3]);
	}
}

void sla_update(int p) {
	int answer;

	for (int i = 0; i < 3; i++) {
		answer = 2 + 2 * i;
		entry_add(answer, board[p / 3][p % 3]);
	}
}

int win_case(void) {
	for (int i = 0; i < 3; i++) {
		if (board[i][0] * board[i][1] * board[i][2] == 0) {
			if (board[i][0] * board[i][1] == squ(2 - ver))
				return (2 + i * 3);
			if (board[i][2] * board[i][0] == squ(2 - ver))
				return (1 + i * 3);
			if (board[i][1] * board[i][2] == squ(2 - ver))
				return (i * 3);
		}

		if (board[0][i] * board[1][i] * board[2][i] == 0) {
			if (board[0][i] * board[1][i] == squ(2 - ver))
				return (2 * 3 + i);
			if (board[2][i] * board[0][i] == squ(2 - ver))
				return (1 * 3 + i);
			if (board[1][i] * board[2][i] == squ(2 - ver))
				return (i);
		}
	}

	for (int i = 0; i < 2; i++) {
		if (board[0][2 * i] * board[1][1] * board[2][2 - 2 * i] == 0) {
			if (board[0][2 * i] * board[1][1] == squ(2 - ver))
				return (2 * 3 + 2 - 2 * i);
			if (board[2][2 - 2 * i] * board[0][2 * i] == squ(2 - ver))
				return (1 * 3 + 1);
			if (board[1][1] * board[2][2 - 2 * i] == squ(2 - ver))
				return (2 * i);
		}
	}

	return (9);
}

int lose_case(void) {
	for (int i = 0; i < 3; i++) {
		if (board[i][0] * board[i][1] * board[i][2] == 0) {
			if (board[i][0] * board[i][1] == squ(ver+1))
				return (2 + i * 3);
			if (board[i][2] * board[i][0] == squ(ver+1))
				return (1 + i * 3);
			if (board[i][1] * board[i][2] == squ(ver+1))
				return (i * 3);
		}

		if (board[0][i] * board[1][i] * board[2][i] == 0) {
			if (board[0][i] * board[1][i] == squ(ver+1))
				return (2 * 3 + i);
			if (board[2][i] * board[0][i] == squ(ver+1))
				return (1 * 3 + i);
			if (board[1][i] * board[2][i] == squ(ver+1))
				return (i);
		}
	}

	for (int i = 0; i < 2; i++) {
		if (board[0][2 * i] * board[1][1] * board[2][2 - 2 * i] == 0) {
			if (board[0][2 * i] * board[1][1] == squ(ver+1))
				return (2 * 3 + 2 - 2 * i);
			if (board[2][2 - 2 * i] * board[0][2 * i] == squ(ver+1))
				return (1 * 3 + 1);
			if (board[1][1] * board[2][2 - 2 * i] == squ(ver+1))
				return (2 * i);
		}
	}

	return (9);
}

int even_count(void) {
	for (int i = 0; i < 4; i++)
		if (board[(2 * i + 1) / 3][(2 * i + 1) % 3] == 0)
			return (2 * i + 1);

	return 0;
}

int odd_count(void) {
	for (int i = 0; i < 5; i++) {
		if (board[(2 * i) / 3][(2 * i) % 3] == 0)
			return (2 * i);
	}
	return 0;
}

void entry_add(int p, int entry) {
	if (entry == 0) {
		heur[p][0] += 2;
		heur[p][1] += 2;
	}
	else if (entry == 1) {
		heur[p][0] += 3;
		heur[p][1] += 1;
	}
	else {
		heur[p][0] += 1;
		heur[p][1] += 3;
	}
}

//square function
int squ(int n) {
	return (n * n);
}

//it returns the index of the max entry of 3 by 3 matrix
int Max_Entry(int A[9][2], int turn) {
	int max;

	for (max = 0; max < 9; max++)
		if (board[max / 3][max % 3] == 0)
			break;

	for (int i = 1; i < 9; i++)
		if (A[i][turn] > A[max][turn] && board[i / 3][i % 3] == 0)
			max = i;

	return (max);
}

//text standardization
void stdtext(void) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 << 4) + 15);
}

//moving the cursor position
void gotoXY(int x, int y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//it returns current cursor position, it isn't used
COORD cur_cur(void) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	COORD answer_coor = { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y };

	return answer_coor;
}

void end_set(int max_columns) {
	const char* str1 = "YOUR WIN!!", * str2 = "YOUR LOSE...",
		* str3 = "PLAYER 1 WIN!!", * str4 = "PLAYER 2 WIN!!", * str5 = "DRAW";

	stdtext();

	if (WorL == 0) {
		gotoXY((max_columns - (int)strlen(str5))/2, 27);
		printf("%s", str5);
	}
	else {
		if (ver == 2) {
			if (WorL == 1) {
				gotoXY((max_columns - (int)strlen(str3)) / 2, 27);
				printf("%s", str3);
			}
			else {
				gotoXY((max_columns - (int)strlen(str4)) / 2, 27);
				printf("%s", str4);
			}
		}
		else {
			if (WorL == 1) {
				gotoXY((max_columns - (int)strlen(str1)) / 2, 27);
				printf("%s", str1);
			}
			else {
				gotoXY((max_columns - (int)strlen(str2)) / 2, 27);
				printf("%s", str2);
			}
		}
	}

	gotoXY(0, 29);
}