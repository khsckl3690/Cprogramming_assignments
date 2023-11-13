#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#define MAX_STR 50

void reorder(char*, int);
void scroll(char*, int);
char* replaceText(char*, char*, char*, int);

main() {
	char* text, * target, * replace;
	text = (char*)malloc(sizeof(char) * MAX_STR);
	target = (char*)malloc(sizeof(char) * MAX_STR);
	replace = (char*)malloc(sizeof(char) * MAX_STR);

	printf("Enter a text : "); gets(text);
	printf("Enter a word to find : "); gets(target);
	printf("Enter a new word : "); gets(replace);

	text=replaceText(text, target, replace, MAX_STR);

	scroll(text, 3);
}

void reorder(char *p, int len) {
	char stor;
	for (int i = 0; i < len - 1; i++) {
		stor = p[i];
		p[i] = p[i + 1];
		p[i + 1] = stor;
	}
}

/*  The statement like "*str = stor;" is unvalid 
 when the pointer variable str points to simply the address of 
 a string, not an array  */

void scroll(char* str, int n)
{
	int len = (int)strlen(str);
	char A[MAX_STR];
	strcpy(A, str);
	A[len++] = ' '; A[len] = '\0';

	while (n-->0)
		for (int j = 0; j < len; j++) {
			system("cls");
			puts(A);
			printf("\n");
			Sleep(100);
			reorder(A, len);
		}
}

char* replaceText(char* text, char* target, char* replace, int maxStr)
{
	char *buffer, *tex_ptr, *checkpoint=text, *repl_ptr;

	if (strcmp(target, "\0") == 0) return (text);

	buffer = (char*)malloc(sizeof(char) * maxStr);
	
	while ((tex_ptr = strstr(checkpoint, target)) != NULL) {
		repl_ptr = replace;
		strcpy(buffer, tex_ptr+strlen(target));
		
		while (*repl_ptr != '\0' && (int)tex_ptr != (int)(text + (maxStr - 2)))
			strncpy(tex_ptr++, repl_ptr++, 1);
		checkpoint = tex_ptr;
		
		while (*buffer != '\0' && (int)tex_ptr != (int)(text + (maxStr - 2)))
			strncpy(tex_ptr++, buffer++, 1);
		*tex_ptr = '\0';
	}
	
	
	char* answer = (char*)malloc(sizeof(char)*maxStr);
	strcpy(answer, text);
	return (answer);
}