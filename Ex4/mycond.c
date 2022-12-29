// taken from https://www.geeksforgeeks.org/condition-wait-signal-multi-threading/
// C program to implement cond(), signal()
// and wait() functions
#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Declaration of thread condition variable
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

// declaring mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int done = 1;

// Thread function
void* foo()
{

	// acquire a lock
	pthread_mutex_lock(&lock);
	if (done == 1) {

		// let's wait on condition variable cond1
		done = 2;
		pthread_cond_wait(&cond1, &lock);
	}
	else {

		// Let's signal condition variable cond1
		pthread_cond_signal(&cond1);
	}

	// release lock
	pthread_mutex_unlock(&lock);


	return NULL;
}

// Driver code
int main()
{
    struct timespec start, finish;
	pthread_t tid1, tid2;
    int i = 0;
    clock_gettime(CLOCK_MONOTONIC, &start );
    while( i  < 1000000){
    // Create thread 1
    done = 1;
	pthread_create(&tid1, NULL, foo, NULL);

	

	// Create thread 2
	pthread_create(&tid2, NULL, foo, NULL);

    i++;
    }
    clock_gettime(CLOCK_MONOTONIC, &finish );
	// wait for the completion of thread 2
	pthread_join(tid2, NULL);

  printf( " the total time is take cond is: %f\n", ((double) (finish.tv_sec - start.tv_sec) + (double)(finish.tv_nsec - start.tv_nsec))/1000000000 );
	return 0;
}
