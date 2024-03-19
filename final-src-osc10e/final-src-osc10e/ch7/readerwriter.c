#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define new_max(x,y) (((x) >= (y)) ? (x) : (y))

/*
This program provides a possible solution for first readers writers problem using mutex and semaphore.
I have used 10 readers and 5 producers to demonstrate the solution. You can always play with these values.
*/

sem_t wrt;
pthread_mutex_t mutex;
int int_counter = 1;
int numreader = 0;

void *writer(void *wno)
{   
    sem_wait(&wrt);
    int_counter = int_counter + 1;
    printf("Writer %d modified cnt to %d\n",(*((int *)wno)),int_counter);
    sem_post(&wrt);

}

void *reader(void *rno)
{   
    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader == 1) {
        sem_wait(&wrt); // If this id the first reader, then it will block the writer
    }
    pthread_mutex_unlock(&mutex);
    // Reading Section
    printf("Reader %d: read cnt as %d\n",*((int *)rno),int_counter);
    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt); // If this is the last reader, it will wake up the writer.
    }
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[])
{   

    if(argc != 4) {
	fprintf(stderr, "Usage: <writers> <readers> <start number>\n");
	return -1;
    }

    int writers_n = atoi(argv[1]);
    int readers_n = atoi(argv[2]);
    int_counter = atoi(argv[3]);
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);

    //Just used for numbering the producer and consumer
    int a[new_max(readers_n, writers_n)]; 
    for(int i = 0; i < new_max(readers_n, writers_n); i++) {
    	a[i] = i+1;
    }
    
    pthread_t read[readers_n];
    for(int i = 0; i < readers_n; i++) {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
    }
    
    pthread_t write[writers_n];
    for(int i = 0; i < writers_n; i++) {
        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
    }

    for(int i = 0; i < readers_n; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < writers_n; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
    
}
