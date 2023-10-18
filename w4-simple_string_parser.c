#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define AL 0
#define NU 1
#define OP 2
#define OT 3

#define MAX_WORD 50
#define MAX_STR 50


/* identifying the types of the arrays */
int type_ident(char *letr) {
	char op[] = "+-*/^";

	char c = *letr;
	letr++;

	if (isalpha(c)) {
		for (int i = 0; i < MAX_WORD, * letr != '\0'; i++) {
			if (isalpha(*letr) == 0)
				return (OT);
			letr++;
		}
		return (AL);
	}

	else if (isdigit(c)) {
		for (int i = 0; i < MAX_WORD, * letr != '\0'; i++) {
			if (isdigit(*letr) == 0)
				return (OT);
			letr++;
		}
		return (NU);
	}

	else if (strchr(op, c)!=NULL) {
		for (int i = 0; i < MAX_WORD, * letr != '\0'; i++) {
			if (strchr(op, *letr) == NULL)
				return (OT);
			letr++;
		}
		return (OP);
	}
	
	else return (OT);
}


/* printing operation */
void print_op(char *word, int type, int i) {
	switch (type) {
	case AL:
		printf("[%d] %s (Alphabets)", i, word);
		break;
	case NU:
		printf("[%d] %s (Numbers)", i, word);
		break;
	case OP:
		printf("[%d] %s (Operators)", i, word);
		break;
	case OT:
		printf("[%d] %s (Others)", i, word);
		break;
	}
	printf("\n");
}


main() {
	int types[MAX_WORD];
	char words[MAX_WORD][MAX_STR];
	int nwords = 0;

	char str[2*MAX_STR], *token;
	char del[] = " \t\n";

	/* Reading Operation Start */
	while (gets(str) != NULL) {
		token = strtok(str, del);
		
		while (token != NULL) {
			strcpy(words[nwords], token);
			nwords++;
			
			token = strtok(NULL, del);
		}
	}
	/* Reading Operation End */

	printf("\n");
	for (int i = 0; i < nwords; i++) {
		types[i]=type_ident(words[i]);
		print_op(words[i], types[i], i + 1);
	}
}