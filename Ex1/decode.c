#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codec.h"

int main(int argc, char *argv[]) {
    if(argc != 3)
    {
        printf("Usage : ./decode <codec> <message>\n");
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
            printf("Usage : ./decode <codec> <message>\n");
        }
        free(output);
    }

    return 0;
    
}