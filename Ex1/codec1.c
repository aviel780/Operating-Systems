#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "codec.h"


void codec1(char *src_text , char *dest_text , int length)
{

    int ch = 0;
    for(int i = 0; i < length; i++)
     {
            ch = src_text[i];
            
            if(isalpha(ch) !=0)
            {
                ch = isupper(ch) > 0 ? tolower(ch) : toupper(ch);
                
            }
            dest_text[i] = ch;
     }

     printf("%s\n",dest_text);
   
}
