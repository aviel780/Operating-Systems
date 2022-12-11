#include <stdio.h>
#include "codec.h"
#include <string.h>

void codec2(char *src_text , char *dest_text , int length)
{

    for(int i=0 ; i < length ; i++)
    {
        dest_text[i] = (char) -src_text[i];
    }

    printf("%s\n",dest_text);


}
