// using https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
#define _POSIX_C_SOURCE 199309L
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


pthread_t thread1;
int counter;
pthread_mutex_t lock;

void* trythis()
{
    int i = 0;
    while(i<1000000){
	pthread_mutex_lock(&lock);

	//unsigned long i = 0;
	//counter += 1;
	//printf("\n Job %d has started\n", counter);
	//printf("\n Job %d has finished\n", counter);

	pthread_mutex_unlock(&lock);
    i++;}
	return NULL;
}

int main(void)
{
     struct timespec start, finish;
	int i = 0;
	int error;

	if (pthread_mutex_init(&lock, NULL) != 0) {
		printf("\n mutex init has failed\n");
		return 1;}
	
    clock_gettime(CLOCK_MONOTONIC, &start );

	
		error = pthread_create(&thread1,NULL,&trythis, NULL);
		if (error != 0){
			printf("\nThread can't be created :[%s]",
				strerror(error));}
		
        pthread_join(thread1, NULL);
	
    clock_gettime(CLOCK_MONOTONIC, &finish );

	printf( " the total time is take mutex is: %f\n", ((double) (finish.tv_sec - start.tv_sec) + (double)(finish.tv_nsec - start.tv_nsec))/1000000000 );

	
	pthread_mutex_destroy(&lock);

	return 0;
}
