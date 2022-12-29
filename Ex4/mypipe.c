// take from chat gpt, writing the quetion: no we check LATENCY how fast can we respond.
// repeat the following tasks 1M time and measure time using accurate watch measure using both processes and sockets/pipes  in c
#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define ITERATIONS 1000000

int main(int argc, char** argv) {
    int pipefd[2];
    struct timespec start, finish;
    long long elapsed_time_ns;
    double elapsed_time_s;

    if (pipe(pipefd) == -1) {  // Create pipe
        perror("pipe");
        return 1;
    }


    pid_t child_pid = fork();  // Create child process
    if (child_pid == -1) {
        perror("fork");
        return 1;
    } 
    else if (child_pid == 0) {
        // Child process
        close(pipefd[1]);  // Close write end of pipe

        char buffer[1];
        while (read(pipefd[0], buffer, sizeof(buffer)) > 0) {  // Read from pipe
            // Respond to message
        }

        close(pipefd[0]);  // Close read end of pipe
        return 0;} 
    
    else {
        // Parent process
        close(pipefd[0]);  // Close read end of pipe

        clock_gettime(CLOCK_MONOTONIC, &start);  // Start timer

        for (int i = 0; i < ITERATIONS; i++) {
            // Parent process continues
            char message[1] = "a";
            write(pipefd[1], message, sizeof(message)); // Write to pipe
                                                        }

    clock_gettime(CLOCK_MONOTONIC, &finish);  // End timer
      printf( " the total time is take cond is: %f\n", ((double) (finish.tv_sec - start.tv_sec) + (double)(finish.tv_nsec - start.tv_nsec))/1000000000 );


    close(pipefd[1]);  // Close write end of pipe
    wait(NULL);  // Wait for child process to finish
    return 0;
}
}


