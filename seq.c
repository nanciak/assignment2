#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 5000
#define K 2500
#define N 5000

int A[M][K];
int B[K][N];
int C[M][N];

void fillMatrix(int *m, int row, int col) {
	for (int i=0; i<row; i++) {
		for (int j=0; j<col; j++) {
			*((m+i*col) + j) = rand()%20;
		}
	}
}


int main() {
	clock_t begin,end;
	begin = clock();
	
	fillMatrix((int*)A,M,K);
	fillMatrix((int*)B,K,N);
	
    	// Perform matrix multiplication
    	for (int i = 0; i < M; i++) {
        	for (int j = 0; j < N; j++) {
            		for (int k = 0; k < K; k++) {
                		C[i][j] += A[i][k] * B[k][j];
            		}
        	}
    	}
  
	end = clock();
	double time = ((double) (end-begin)) / CLOCKS_PER_SEC;
	printf("Time taken: %.5f", time);
    	return 0;
}

