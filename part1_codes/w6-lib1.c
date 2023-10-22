#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void read_op(Sborrow*);
void ymd(char*, Sborrow*);
void save_print(Sborrow *, int);

main() {
	Sborrow A[MAX_MEM], *p=A;
	
	char str[MAX_STR];
	int num=0;

	printf("Enter the book title: ");
	gets(str);

	while (*str != '\0') {
		strcpy(A[num].booktitle, str);
		read_op(p);
		getchar();

		num++; p++;
		
		printf("Enter the book title: ");
		gets(str);
	}

	save_print(A, num);
}

void read_op(Sborrow* p) {
	char str[MAX_STR];

	printf("Enter the borrower: ");
	gets(str);
	strcpy(p->name, str);

	printf("Enter the phone number: ");
	gets(str);
	strcpy(p->telephone, str);

	printf("Enter the due date: ");
	gets(str);
	ymd(str, p);
}

void ymd(char* str, Sborrow* p) {
	char A[MAX_STR];

	strncpy(A, str, 4); A[4] = '\0';
	p->due.year= atoi(A);

	strncpy(A, str+4, 2); A[2]='\0';
	p->due.month=atoi(A);
	
	strncpy(A, str+6, 2); A[2]='\0';
	p->due.day=atoi(A);
}

void save_print(Sborrow *A, int num) {
	for (int i = 0; i < num; i++) {
		printf("\n");
		printf("Book title: %s\n", A->booktitle);
		printf("Borrower: %s\n", A->name);
		printf("Telephone: %s\n", A->telephone);
		printf("Due date: %d. %02d. %02d\n", A->due.year, A->due.month, A->due.day);

		A++;
	}
}