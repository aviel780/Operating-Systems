// taken from https://www.informit.com/articles/article.aspx?p=23618&seqNum=4
#define _POSIX_C_SOURCE 199309L
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main (int argc, char* argv[])
{
struct timespec start, finish;

 int fd;
 struct flock lock;

 /* Open a file descriptor to the file. */
 fd = open ("file_text_for_fcntl.txt", O_CREAT |O_WRONLY);
 if (fd == -1)
 {
    printf("error in opening the file");
 }
 
clock_gettime(CLOCK_MONOTONIC, &start );
 int i = 0;
 while(i<1000000){
    /* Initialize the flock structure. */
    memset (&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;

    /* Place a write lock on the file. */
    fcntl (fd, F_SETLKW, &lock);

    /* Release the lock. */
    lock.l_type = F_UNLCK;
    fcntl (fd, F_SETLKW, &lock);
    i++;}
clock_gettime(CLOCK_MONOTONIC, &finish );
 close (fd);
   printf( " the total time is take fctnl is: %f\n", ((double) (finish.tv_sec - start.tv_sec) + (double)(finish.tv_nsec - start.tv_nsec))/1000000000 );

 return 0;
}