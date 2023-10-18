#include <stdio.h>
#define N 5

void printArray(int A[][5], int n);

void spiralArray(int A[][5], int n) {
	int * p=A;
	int i;
	for (i = 0; i < n; i++)
	{
		*p=i+1;
		p++;
	}
	i--;
	p--;
	int code = 0, num = 5;
	for (i; i >0; i--) {	
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < i; k++) {
				if (code % 4 == 0)
					p += n;
				else if (code % 4 == 1)
					p -= 1;
				else if (code % 4 == 2)
					p -= n;
				else p += 1;
				num++;
				*p = num;
			}
			code++;
		}
	}
}

void printArray(int A[][5], int n) {
	int* p = A;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%03d ", *p);
			if (i == n-1 && j == n-1);
			else p++;
		}
		printf("\n\n");
	}
}

main() {
	int A[5][5];
	spiralArray(A, N);
	printArray(A, N);
}
