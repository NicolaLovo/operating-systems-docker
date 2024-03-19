#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N_THREADS 2

// Global vars
int *sumArray_pt, *sumArray_omp, *arr1, *arr2;
int thrID = 0;
int size = 10;


// Support Functions

void* sum_funct(void* arg){

    int thread_ID = thrID++; 
 
    for (int k = thread_ID * (size / N_THREADS); k < (thread_ID + 1) * (size / N_THREADS); k++) {
	sumArray_pt[k] = arr1[k] + arr2[k];
    }

}

void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void pthread_sum(){

	void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

}


int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr,"usage: a.out <integer value>\n");
		/*exit(1);*/
		return -1;
	}

	if (atoi(argv[1]) < 0) {
		fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
		/*exit(1);*/
		return -1;
	}
	
	// Create Arrays
	size = atoi(argv[1]);
	arr1 = (int*) malloc(sizeof(int)*size);
	arr2 = (int*) malloc(sizeof(int)*size);
	sumArray_pt = (int*) malloc(sizeof(int)*size);
	sumArray_omp = (int*) malloc(sizeof(int)*size);
	for(int i=0;i<size;i++){
		arr1[i] = rand() % 999;
		arr2[i] = rand() % 999;
	}
	
	// Pthread Sum
	clock_t t1, t2;
	pthread_t threads[N_THREADS];
	t1 = clock();
	for (int i = 0; i < N_THREADS; i++) 
             pthread_create(&threads[i], NULL, sum_funct, (void*)NULL); 
        for (int i = 0; i < N_THREADS; i++) 
	     pthread_join(threads[i], NULL); 
	t2 = clock();
	double pt_time = (double)(t2-t1)/CLOCKS_PER_SEC;
	
	// OMP Sum
	t1 = clock();
	#pragma omp parallel for reduction (+:sumArray_omp)
	for (int i=0;i<size;i++)
	     sumArray_omp[i] = arr1[i] + arr2[i];
	t2 = clock();
	double omp_time = (double)(t2-t1)/CLOCKS_PER_SEC;
	
	if (size < 20){
		printf("array 1: \n");
		printArray(arr1, size);
		printf("array 2: \n");
		printArray(arr2, size);
		printf("sum array: \n");
		printArray(sumArray_omp, size);
	}
	printf("\tPT Time: %.5f, OMP Time: %.5f\n",pt_time, omp_time);
	return 0;
}

