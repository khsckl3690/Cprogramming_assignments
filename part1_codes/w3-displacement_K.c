#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>

#define LEN 100

char func(char a, int b, int k) {
	int p= (int)a + k;
	if (b == 1) {
		if (p > 90)
			p -= 26;
	}
	else {
		if (p > 122)
			p -= 26;
	}
	return ((char)p);
}

void coding(char* p, int k) {
	int id;
	for (int i = 0; *p!='\0'; i++) {
		id=isalpha(*p);
		if (id != 0)
			*p = func(*p, id, k);
		p++;
	}
}

main() {
	char str[LEN];
	int k;
	scanf("%d", &k);
	getchar();
	gets(str);
	coding(str, k);
	puts(str);
}