nc.
we nedd to implement a client server.
when we type nc-L we need to give the port and its will be the server
in nc-L we need to get from the client the data and print at on the stdout.

nc is the client and he get 2 permeters. ip and port. in mode we whrite the data on the stdin an sent at to the server.

use. 
gcc -g -o mync mync.c
we open 2 windos
in window 1 we print nc-L <port> to open the server:
./mync nc-L 8080
Socket successfully created..
Socket successfully binded..
Server listening..
server accept the client...


in window 2 we print nc <ip> <port> to open the client:
./mync nc 127.0.0.1 8080
Socket successfully created..
connected to the server..

then what we wrhit on window 2 will show on window 1.

window 2:
Enter the string : hello
Enter the string : the code is working
Enter the string : its a good code
Enter the string : thank you

window 1:
hello
the code is working
its a good code
thank you

and that what we asking for.
in this part we use the web site for help:https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
comment: somtimes the conecsion with the server dont secsees in the first attemp, try intil its will work.

tee function:
in this part we nedd to implemnet the tee function.
what we wrhit in the stdin will shon in stdout and we will get a txt file who have all what we wrot.

use:
gcc -g -o tee mytee.c
format: ./mytee <file name output>

 gcc -g -o tee mytee.c
 ./tee outputfile
 asd
d
its working
yes
ok

you can see thos words in the output file we upload the git in name outputfile.
