#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 20
#define M 5000
#define K 1000
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

struct thread_data {
	int thread_id;
    	int start_row;
    	int end_row;
};

void * multiply_matrix(void * threadarg) {
    	struct thread_data *data = (struct thread_data *) threadarg;
    	int thread_id = data->thread_id;
    	int start_row = data->start_row;
    	int end_row = data->end_row;

    	for (int i = start_row; i <= end_row; i++) { //rows from the first matrix A
        	for (int j = 0; j < N; j++) { //colums of the second matrix B
        	    for (int k = 0; k < K; k++) {
        	        C[i][j] += A[i][k] * B[k][j];
        	    }
       		}
    	}
    	pthread_exit(NULL);
}

int main() {

	clock_t start,end;
	double t2;
	start = clock();
	

	fillMatrix((int*)A,M,K);
	fillMatrix((int*)B,K,N);
	
   	 pthread_t threads[NUM_THREADS];
    	struct thread_data thread_data_array[NUM_THREADS];
    	int rc, t;

    	int rows_per_thread = M / NUM_THREADS;
    	int extra_rows = M % NUM_THREADS;
    	int start_row = 0;
    	int end_row = -1;

	
    	for (t = 0; t < NUM_THREADS; t++) {
        	end_row = start_row + rows_per_thread - 1;
       		if (extra_rows > 0) {
            		end_row++;
            		extra_rows--;
        	}

        	thread_data_array[t].thread_id = t;
        	thread_data_array[t].start_row = start_row;
        	thread_data_array[t].end_row = end_row;

        	rc = pthread_create(&threads[t], NULL, multiply_matrix, (void *)&thread_data_array[t]);
        	if (rc) {
            		printf("Error: return code from pthread_create() is %d\n", rc);
            		exit(-1);
        	}

        	start_row = end_row + 1;
    	}

    	// Wait for all threads to complete
    	for (t = 0; t < NUM_THREADS; t++) {
        	pthread_join(threads[t], NULL);
    	}


	end = clock();
	t2 = ((double) end - start) / CLOCKS_PER_SEC;
	printf("Time taken: %.4f s",t2);
    	return 0;
}
