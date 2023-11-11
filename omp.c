#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <omp.h>

#define M 5000
#define K 2500
#define N 5000

#define NUM_THREADS 20

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
	double start_time, end_time;
	
	fillMatrix((int*)A,M,K);
	fillMatrix((int*)B,K,N);
	
	start_time = omp_get_wtime();
	omp_set_num_threads(NUM_THREADS);
	int i,j,k;
	
	
	#pragma omp parallel for private(i,j,k) shared(A,B,C)
    	for (i = 0; i < M; i++) {
       		for (j = 0; j < N; j++) {
      		      for (k = 0; k < K; k++) {
                		C[i][j] += A[i][k] * B[k][j];
            		}
        	}
  	  }
	
	    end_time = omp_get_wtime() - start_time;
	    
	    printf("Time taken: %.5f", end_time);
	    return 0;
}
