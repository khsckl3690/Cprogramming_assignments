#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 10

void star(int n) {
	while (n-- > 0)
		printf("*");
}

void print(int n, int a[]) {
	for (int i = 0; i <= n; i++) {

		printf("%02d[%2.3f]:", i, (float)a[i]);
		star(a[i]);
		printf("\n");
	}
}

void array_init(int n, int a[]) {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100; i++)
		a[casing()]++;
}

int casing(void) {
	int total = 0;
	for (int i = 0; i < 10; i++) {
		int value = rand() % 2 + 0;
		if (value == 1) total++;
	}
	return (total);
}

main() {
	int a[NUM+1]={0};
	array_init(NUM, a);
	print(NUM, a);
}
