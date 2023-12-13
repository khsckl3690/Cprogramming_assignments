#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define MAX_STR 150

typedef struct _word {
	char* word;
	char* meaning;
} Sword;

Sword* dictionary = NULL;
int nwords = 0;

void file_read(void);
int words_count(FILE*);
void dict_mall(void);
void word_mall(int, size_t);
void mean_mall(int, size_t);
int first_step(void);
int fs_judge(void);
int digitcheck(int);
void oper_1(void);
void oper_2(void);
void oper_3(void);
void set_seed(void);
int ith_allo(int A[], int);
int ith_que(int A[], int);
int que_allo(void);
int answer_allo(void);

int main(){
	file_read();

	int mode;

	while (1) {
		mode = first_step();

		system("cls");
		switch (mode) {
		case 1:
			oper_1();
			break;
		case 2:
			oper_2();
			break;
		case 3:
			oper_3();
			break;
		case 0:
			exit(0);
		}

		system("cls");
	}

	return 0;
}

void file_read(void) {
	FILE* fp;
	fp = fopen("voca13000.txt", "r");

	char bf[MAX_STR], *token;
	const char* del = " \t", *del_1 = "\n";

	while (fgets(bf, MAX_STR, fp) != NULL)
		nwords++;

	dict_mall();
	rewind(fp);

	for (int i = 0; fgets(bf, MAX_STR, fp) != NULL; i++) {
		token = strtok(bf, del);

		word_mall(i, strlen(token) + 1);
		strcpy(dictionary[i].word, token);

		token = strtok(NULL, del_1);

		mean_mall(i, strlen(token) + 1);
		strcpy(dictionary[i].meaning, token);
	}
	
	fclose(fp);
}

int words_count(FILE* fp) {
	FILE* copy = fp;
	char bf[MAX_STR];
	int count = 0;

	while (fgets(bf, MAX_STR, copy)!=NULL)
		count++;

	fclose(copy);
	return (count);
}

void dict_mall(void) {
	dictionary = (Sword*)malloc(sizeof(Sword) * nwords);
}

void word_mall(int index, size_t len) {
	dictionary[index].word = (char*)malloc(sizeof(char) * len);
}

void mean_mall(int index, size_t len) {
	dictionary[index].meaning = (char*)malloc(sizeof(char) * len);
}

int first_step(void) {
	system("cls");

	puts("  ### Dictionary ###");
	puts("1. Search a word");
	puts("2. List words");
	puts("3. Word Game - Find Meaning");
	puts("0. Exit");
	printf("\nEnter the command: ");

	return (fs_judge());
}

int fs_judge(void) {
	char str[MAX_STR];

	gets(str);
	int n = atoi(str);

	if (strlen(str) == 1 && digitcheck(n)) {
		return (n);
	}

	return (first_step());
}

int digitcheck(int n) {
	if (n >= 0 && n < 4)
		return (1);

	return (0);
}

void oper_1(void) {
	int bot = 0, top = nwords - 1, p;
	char cmpWord[MAX_STR];

	printf("Enter a word to search: ");
	gets(cmpWord);
	int n;

	for (int i = 0; i < 100; i++) {
		p = (bot + top) / 2;

		if ((n = strcmp(cmpWord, dictionary[p].word)) < 0) top = p;
		if (n > 0) bot = p + 1;
		if (n == 0 || bot == top) break;

	}
	if (bot == top && n != 0)
		puts("\nThere's no such a word");
	else {
		printf("\n%-20s %s\n", dictionary[p].word, dictionary[p].meaning);
	}

	printf("\nPress any button to continue...");
	_getch();
		
}

void oper_2(void) {
	int q;
	for (int i = 0; 1; i++) {
		system("cls");
		for (int j = 0; j < 15; j++) {
			printf("%-20s %s\n", dictionary->word, dictionary->meaning);
			dictionary++;
		}

		printf("Press any button except for 'q' to continue...");
		q = _getch();
		if (q == 'q') {
			dictionary = &dictionary[0];
			break;
		}
	}
}

void oper_3(void) {
	set_seed();
	int que[10] = { 0 }, corr[10] = { 0 }, score=0;

	//determinating the index of the questions
	for (int i = 0; i < 10; i++) {
		ith_allo(que, i);
		corr[i] = ith_que(que, i);
		printf("\n\n");

		score += corr[i];
	}

	printf("Your Score is %d (correct %d out of 10 problems)\n\n", score*10, score);

	if (score != 10) {
		printf("Wrong problems\n\n");
		for (int i = 0; i < 10; i++)
			if (corr[i] == 0)
				printf("[%d] %-20s %s\n", i + 1, dictionary[que[i]].word, dictionary[que[i]].meaning);
	}
	
	printf("\nPress any button to continue...");
	_getch();
}

int ith_allo(int que[], int i) {
	que[i] = que_allo();

	for (int j = 0; j < i; j++)
		if (que[j] == que[i])
			return (ith_allo(que, i));

	return 0;
}

int ith_que(int que[], int i) {
	int answer = answer_allo(), mean_stor[4] = { que[i], 0, 0, 0 }, j = 0;
	char str_bundle[3][MAX_STR];

	for (int k = 0; k < 3; k++) {
		ith_allo(mean_stor, k + 1);
		strcpy(str_bundle[k], dictionary[mean_stor[k + 1]].meaning);
	}

	printf("%d. %s\n", i + 1, dictionary[que[i]].word);
	printf("\ta. %s\n", (answer == 1) ? dictionary[que[i]].meaning : str_bundle[j++]);
	printf("\tb. %s\n", (answer == 2) ? dictionary[que[i]].meaning : str_bundle[j++]);
	printf("\tc. %s\n", (answer == 3) ? dictionary[que[i]].meaning : str_bundle[j++]);
	printf("\td. %s\n", (answer == 4) ? dictionary[que[i]].meaning : str_bundle[j++]);
	printf("\tAnswer : ");

	if (getchar() == 'a' + (answer - 1)) {
		getchar();
		return 1;
	}
	else {
		getchar();
		return 0;
	}
}

void set_seed(void) {
	srand((unsigned)time(NULL));
}

int que_allo(void) {
	return (rand() % nwords + 0);
}

int answer_allo(void) {
	return (rand() % 4 + 1);
}