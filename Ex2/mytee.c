#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 1024

//declerison on the functions
int creat_file(char* x);
int wriht_to_file(int s);


int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        fprintf(stderr, "%s\n", "you dont give filename output");
        exit(1);
    }

    char * fileout = argv[1];
    // creating the file
    int s = creat_file(fileout);
    //write the data from the terminel to the file
    wriht_to_file(s);
    //close the file in the end of writing
    fclose(fileout);
    return 0;
}

int creat_file(char* fileout){
    // opening the file and give atoreiz to this file()
    //o_creat- if the file dont exsist it creat him if is exsist its dont do nothing
    //o_wronly - opning for wriht only
    //O_TRUNC - If the file exists and is a regular file, and the file is successfully opened , its length shall be truncated to 0, and the mode and owner shall be unchanged.
 int fp = open(fileout, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    // -1 its mean the file dont opneing
    if (fp == -1) {
        fprintf(stderr, "%s\n", "file dont opening");
        exit(1);
    }
    return fp;
}

int wriht_to_file(int p){
    char buffer[MAX] = {0};
    unsigned int readf = 0;
    int s;
    // read - read 1024 bytes to the buffer from stdin(what we wriht in the terminel)
    while((readf = read(STDIN_FILENO, buffer, 1024)) != 0) {
        //write = wriht readf bytes from the buffer to p file
        s = write(p, buffer, readf);
        if (s != readf) {
            fprintf(stderr, "%s\n", "cant write to the file");
            exit(1);
        }
    };
}