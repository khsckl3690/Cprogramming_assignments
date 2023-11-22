#include <stdio.h>
#define N 5

void spiralArray(int A[][N], int n) {
	int * p=A[0];
	for (int i = 0; i < n; i++)
	{
		*p=i+1;
		p++;
	}
	p--;

	int code = 0, num = n;
	for (int i=0; i <n-1; i++) {	
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < n-i-1; k++) {
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

void printArray(int A[][N], int n) {
	int* p = A[0];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%2d ", *p);
			p++;
		}
		printf("\n\n");
	}
}

main() {
	int A[N][N];
	spiralArray(A, N);
	printArray(A, N);
}
