#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STR 100
#define MAX_MEM 100


typedef struct struct_date {
	int year, month, day;
} Sdate;

typedef struct struct_borrow {
	char booktitle[MAX_STR]; // 책 제목
	char name[MAX_STR]; // 대출자 이름
	char telephone[MAX_STR]; // 전화번호(문자열로 저장)
	Sdate due; // 반납기한
} Sborrow;

Sborrow A[MAX_MEM], * p = A;
int num = 0;

int com_read(void);
void read_1(void);
void read_2(Sborrow*);
void save_print(void);
void oper_3(void);
void oper_4(void);

main() {
	while (1) {
		switch (com_read()) {
		case 0:
			exit(0);
			break;
		case 1:
			read_1();
			break;
		case 2:
			save_print();
			break;
		case 3:
			oper_3();
			break;
		case 4:
			oper_4();
			break;
		default:
			printf("Wrong command. Enter again \n\n");
			continue;
		}
		printf("\n\n");
		printf("Press any key to continue...");
		_getch();
		printf("\n\n");
	}
}

void read_1(void) {
	char str[MAX_STR];

	printf("Enter the book title: ");
	gets(str);

	if (*str != '\0') {
		strcpy(A[num].booktitle, str);
		
		read_2(p);
		getchar();

		num++; p++;
	}
	else printf("Nothing entered. ");
}

void read_2(Sborrow* p) {
	char str[MAX_STR];

	printf("Enter the borrower: ");
	gets(str);
	strcpy(p->name, str);

	printf("Enter the phone number: ");
	gets(str);
	strcpy(p->telephone, str);

	printf("Enter the due date: ");
	scanf("%4d %2d %2d", &p->due.year, &p->due.month, &p->due.day);

}

void save_print(void) {
	Sborrow* p = A;

	printf("** Borrowed books **\n");
	for (int i = 0; i < num; i++) {
		printf("\n");
		printf("[%d]Book title: %s\n", i+1, p->booktitle);
		printf("   Borrower: %s\n", p->name);
		printf("   Telephone: %s\n", p->telephone);
		printf("   Due date: %d. %02d. %02d", p->due.year, p->due.month, p->due.day);

		p++;
	}
}

int com_read(void) {
	char str[MAX_STR];
	int command;
	printf("1. Add a borrow\n2. Print the list\n3. Book search\n4. Due date has passed!\n0. Quit the program\nEnter the command : ");

	gets(str);
	printf("\n");
	command = atoi(str);

	return (command);
}

void oper_3(void) {
	char str[MAX_STR], *p;
	int n = 0;

	printf("Enter the keyword of the title to search: ");
	gets(str);
	for (int i=0; i<num; i++)
		if (strstr(A[i].booktitle, str)) {
			printf("[%d] %s, %s, %d.%02d.%02d\n", 
				++n,
				A[i].booktitle,
				A[i].name,
				A[i].due.year,
				A[i].due.month,
				A[i].due.day);
		}

}

void oper_4(void) {
	time_t curr;
	struct tm* d;
	int ident[MAX_MEM] = { 0 }, n=0;
	char pass[] = "Due date has passed!!!\n\n";

	curr = time(NULL);
	d = localtime(&curr);

	printf("Today: %d. %02d. %02d\n\n", d->tm_year + 1900, d->tm_mon + 1, d->tm_mday);

	for (int i = 0; i < num; i++) {
		if (A[i].due.year > d->tm_year + 1900);
		else if (A[i].due.year == d->tm_year + 1900 && A[i].due.month > d->tm_mon + 1);
		else if (A[i].due.year == d->tm_year + 1900 && A[i].due.month == d->tm_mon + 1 && A[i].due.day >= d->tm_mday);
		else ident[i] = 1;
	}

	for (int j = 0; j < num; j++)
		if (ident[j]) {
			printf("%s", pass);
			*pass = '\0';
			printf("[%d] %s, %s, %d.%02d,%02d\n",
				++n,
				A[j].booktitle,
				A[j].name,
				A[j].due.year,
				A[j].due.month,
				A[j].due.day);
		}
}