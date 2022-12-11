#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "codec.h"

int main(int argc, char *argv[]) {
    if(argc != 3)
    {
        printf("Usage : ./encode <codec> <message>");
    }
    else
    {
        int length = strlen(argv[2]);
        char *output = malloc(length * sizeof(char));

        char *codec = argv[1];

        if(strcmp(codec,"codec1") == 0) codec1(argv[2],output,length);
        else if(strcmp(codec,"codec2") == 0) codec2(argv[2],output,length);
        else
        {
            printf("Usage : ./encode <codec> <message>");
        }
        free(output);
    }
    
    return 0;
    
}