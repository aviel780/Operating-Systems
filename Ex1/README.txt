the contens of the folder is:
aviavi@aviavi-VirtualBox:~/Desktop/os/Ex1$ ls
cmp.c     codec2.c  copy.c    encode.c   file3.txt  Makefile
codec1.c  codec.h   decode.c  file1.txt  file4.txt  README.txt

we use the comend make all and we get the flowing comends:
gcc -Wall -g -o cmp cmp.c
gcc -Wall -g -o copy copy.c
gcc -Wall -g -c codec1.c
gcc -shared -o codec1.so codec1.o
gcc -Wall -g -c codec2.c
gcc -shared -o codec2.so codec2.o
gcc -Wall -g -c encode.c
gcc -Wall -g -o encode encode.o ./codec1.so ./codec2.so -lm -ldl
gcc -Wall -g -c decode.c
gcc -Wall -g -o decode decode.o ./codec1.so ./codec2.so -lm -ldl

we can see thet the files was add to the folder:
aviavi@aviavi-VirtualBox:~/Desktop/os/Ex1$ ls
cmp       codec1.so  codec.h  decode.c  encode.o   Makefile
cmp.c     codec2.c   copy     decode.o  file1.txt  README.txt
codec1.c  codec2.o   copy.c   encode    file3.txt
codec1.o  codec2.so  decode   encode.c  file4.txt.

we do the comend make clen:
aviavi@aviavi-VirtualBox:~/Desktop/os/Ex1$ make clean
rm -f decode encode copy cmp *.o *.so

also the make clean delet the files we asket for:
aviavi@aviavi-VirtualBox:~/Desktop/os/Ex1$ ls
cmp       codec1.so  codec.h  decode.c  encode.o   Makefile
cmp.c     codec2.c   copy     decode.o  file1.txt  README.txt
codec1.c  codec2.o   copy.c   encode    file3.txt
codec1.o  codec2.so  decode   encode.c  file4.txt

now we do aome test on the files.
we see a identical fiels in the cmp.c files
aviavi@aviavi-VirtualBox:~/Desktop/os/Ex1$ ./cmp file1.txt file4.txt
Identical
and not when they are not:

aviavi@aviavi-VirtualBox:~/Desktop/os/Ex1$ ./cmp file1.txt file3.txt
Not identical

the copy operison:
aviavi@aviavi-VirtualBox:~/Desktop/os/Ex1$ ./copy file1.txt file3.txt
file is copied.

the encode with codec1:
aviavi@aviavi-VirtualBox:~/Desktop/os/Ex1$ ./encode codec1 LALAlala2345
lalaLALA2345

the decode with codec1:
aviavi@aviavi-VirtualBox:~/Desktop/os/Ex1$ ./decode codec1 LALAlala2345
lalaLALA2345

the encode with codec2:
aviavi@aviavi-VirtualBox:~/Desktop/os/Ex1$ ./encode codec2 LALAlala2345
������������

the decode with codec2:
aviavi@aviavi-VirtualBox:~/Desktop/os/Ex1$ ./decode codec2  LALAlala2345
������������



we use the flowing website to help with parts in ouer code.
cmp = https://codeforwin.org/2018/02/c-program-compare-two-files.html

