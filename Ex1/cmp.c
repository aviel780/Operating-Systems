/**
 * taken from codeforwin
 */

#include <stdio.h>
#include <stdlib.h>

/* Function declaration */
int compareFile(FILE * fPtr1, FILE * fPtr2, int * line, int * col);


int main(int argc,char* argv[])
{
    /* File pointer to hold reference of input file */
    FILE * fPtr1; 
    FILE * fPtr2;

    int diff;
    int line, col;


    if(argc == 3)
    {
        /*  Open all files to compare */
        fPtr1 = fopen(argv[1], "r");
        fPtr2 = fopen(argv[2], "r");

        /* fopen() return NULL if unable to open file in given mode. */
        if (fPtr1 == NULL || fPtr2 == NULL)
        {
        /* Unable to open file hence exit */
           printf("Usage : cmp <file1> <file2>");
        }


        /* Call function to compare file */
         diff = compareFile(fPtr1, fPtr2, &line, &col);

         if (diff == 0)
         {
             printf("Identical\n");
         }
         else 
         {
        printf("Not identical\n");
        
            }


         /* Finally close files to release resources */
        fclose(fPtr1);
        fclose(fPtr2);
    }
    else
    {
        printf("Usage : cmp <file1> <file2>\n");
    }
    

    return 0;
}


/**
 * Function to compare two files.
 * Returns 0 if both files are equivalent, otherwise returns
 * -1 and sets line and col where both file differ.
 */
int compareFile(FILE * fPtr1, FILE * fPtr2, int * line, int * col)
{
    char ch1, ch2;

    *line = 1;
    *col  = 0;

    do
    {
        // Input character from both files
        ch1 = fgetc(fPtr1);
        ch2 = fgetc(fPtr2);
        
        // Increment line 
        if (ch1 == '\n')
        {
            *line += 1;
            *col = 0;
        }

        // If characters are not same then return -1
        if (ch1 != ch2)
            return -1;

        *col  += 1;

    } while (ch1 != EOF && ch2 != EOF);


    /* If both files have reached end */
    if (ch1 == EOF && ch2 == EOF)
        return 0;
    else
        return -1;
}