#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>

bool IsLink(char *argv[],int index);
void DeepCopy(char *src_path,char *dest_path);
void Copy(char *argv[],char *src_path, char *dest_path, bool is_link , bool option);

void Copy(char *argv[],char *src_path, char *dest_path, bool is_link , bool option)
{
    if(is_link)
    {
        int bufSize = 256;
        char *buf = malloc(bufSize * sizeof(char));
        char *link = src_path;

        
        int linkSize = readlink(link, buf, bufSize);

        while (linkSize + 1 == bufSize)
         {
            free(buf);
            bufSize *= 2;
            buf = malloc(bufSize * sizeof(char));
            linkSize = readlink(link, buf, bufSize);
         }
            
        buf[linkSize] = '\0';
        if(option == true)
        {
            
             if (symlink(buf, src_path) != 0)
             {
                    perror("symlink() error");
                    unlink(src_path);
             }
        
             printf("\nfile is copied.\n");

        }
        else
        {
            DeepCopy(buf,dest_path);
        }
    }
    else
    {
        DeepCopy(src_path,dest_path);
    }
}

void DeepCopy(char *src_path,char *dest_path)
{
    FILE *src_file;
    FILE *dest_file;

    src_file = fopen(src_path,"r");
    dest_file = fopen(dest_path,"w");
    

    if(src_file == NULL || dest_file == NULL)
    {
        printf("Usage : copy <file1> <file2>\n");
    }
    else
    {
         char ch = fgetc(src_file);
         while (ch != EOF)
         {
       
            fputc(ch,dest_file);

        
            ch = fgetc(src_file);
        }


    printf("file is copied.\n");


   
    fclose(src_file);
    fclose(dest_file);
    }

}

bool IsLink(char *argv[],int index)
{
    struct stat path;
    lstat(argv[index],&path);

    \
    if(S_ISLNK(path.st_mode))
    {
        return true;
    } 
    else 
    {
        return false;
    }
}






int main(int argc,char* argv[])
{
    
    if(argc < 3 || argc > 4)
    {
        printf("Usage : copy <file1> <file2>\n");
        return 0;
    }
    
    bool is_link;
    
    if(argc == 3)
    {
       is_link = IsLink(argv,1);
       Copy(argv,argv[1],argv[2],is_link,false);
    }
    else if(argc == 4)
    {
        is_link = IsLink(argv,2);
        int option = getopt(argc, argv, ":if:lrx");
        
        if(option == 'l' || option == 'L')
        {
          Copy(argv,argv[2],argv[3],is_link,true);
        }
        else
        {
            printf("Usage : copy <file1> <file2>\n");
        }
    }
    else
    {
        printf("Usage : copy <file1> <file2>\n");
    }



    return 0;
}