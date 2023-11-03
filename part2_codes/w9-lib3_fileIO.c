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

Sborrow A[MAX_MEM];
int num = 0;
const char* file_name = "load file.txt";

int com_read(void);
void read_1(void);
void read_2(void);
void save_print(void);
void oper_3(void);
void oper_4(void);
void oper_5(void);
void oper_6(void);
void oper_7(void);

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
		case 5: 
			oper_5();
			break;
		case 6:
			oper_6();
			break;
		case 7:
			oper_7();
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

		read_2();
		getchar();

		num++;
	}
	else printf("Nothing entered. ");
}

void read_2(void) {
	char str[MAX_STR];

	printf("Enter the borrower: ");
	gets(str);
	strcpy(A[num].name, str);

	printf("Enter the phone number: ");
	gets(str);
	strcpy(A[num].telephone, str);

	printf("Enter the due date: ");
	scanf("%4d %2d %2d", &A[num].due.year, &A[num].due.month, &A[num].due.day);

}

void save_print(void) {
	Sborrow* books = A;

	printf("** Borrowed books **");
	for (int i = 0; i < num; i++) {
		printf("\n\n");
		printf("[%d]Book title: %s\n", i + 1, books->booktitle);
		printf("   Borrower: %s\n", books->name);
		printf("   Telephone: %s\n", books->telephone);
		printf("   Due date: %d. %02d. %02d", books->due.year, books->due.month, books->due.day);

		books++;
	}
}

int com_read(void) {
	char str[MAX_STR];
	int command;
	puts("1. Add a borrow");
	puts("2. Print the list"); 
	puts("3. Book search");
	puts("4. Due date has passed!");
	puts("5. Sort the book list");
	puts("6. Save the book list");
	puts("7. Load the book list");
	puts("0. Quit the program");
	printf("Enter the command : ");

	gets(str);
	printf("\n");
	command = atoi(str);

	return (command);
}

void oper_3(void) {
	char str[MAX_STR];
	int n = 0;

	printf("Enter the keyword of the title to search: ");
	gets(str);
	for (int i = 0; i < num; i++) {
		printf("\n\n");
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

}

void oper_4(void) {
	time_t curr;
	struct tm* d;
	int ident[MAX_MEM] = { 0 }, n = 0;
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

void oper_5(void) {

}

void oper_6(void) {
	FILE* fp;

	fp = fopen(file_name, "w");
	
	for (int i = 0; i < num; i++) {
		fputs(A[i].booktitle, fp);
		fprintf(fp, "\n");

		fputs(A[i].name, fp);
		fprintf(fp, "\n");
		
		fputs(A[i].telephone, fp);
		fprintf(fp, "\n");
		
		fprintf(fp, "%04d%02d%02d", A[i].due.year, A[i].due.month, A[i].due.day);
		fputs("\n\n", fp);
	}
	fclose(fp);
	printf("Save process of %d elements successful", num);
}

void oper_7(void) {
	FILE* fp;

	fp = fopen(file_name, "r");
	
	char bf[MAX_STR];

	while (fgets(bf, MAX_STR, fp) !=NULL) {
		strcpy(A[num].booktitle, bf);
		A[num].booktitle[strcspn(A[num].booktitle, "\n")] = '\0';

		fgets(A[num].name, MAX_STR, fp);
		A[num].name[strcspn(A[num].name, "\n")] = '\0';
		
		fgets(A[num].telephone, MAX_STR, fp);
		A[num].telephone[strcspn(A[num].telephone, "\n")] = '\0';

		fscanf(fp, "%4d%2d%2d", 
			&A[num].due.year, &A[num].due.month, &A[num].due.day);

		num++;
		fgetc(fp); fgetc(fp);
	}
	fclose(fp);
	printf("Loading process of %d elements successful", num);
}