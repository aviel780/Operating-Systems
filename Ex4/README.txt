208244012
we asist the webs
mutex - https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
fctnl- https://www.informit.com/articles/article.aspx?p=23618&seqNum=4
pipe - chat gpt, writing the quetion: no we check LATENCY how fast can we respond.repeat the following tasks 1M time and measure time using accurate watch measure using both processes and sockets pipes  in c
cond - https://www.geeksforgeeks.org/condition-wait-signal-multi-threading/


aviavi@aviavi-VirtualBox:~/Desktop/os/Ex4$ make all
gcc -pthread -o mutex mymutex.c
gcc -pthread -o fctnl myfctnl.c
gcc -pthread -o cond mycond.c
gcc -pthread -o pipe mypipe.c
aviavi@aviavi-VirtualBox:~/Desktop/os/Ex4$ make run
./mutex 
 the total time is take mutex is: 0.015968
./fctnl 
 the total time is take fctnl is: -0.171741
./cond 
 the total time is take cond is: 0.710627
./pipe
 the total time is take pipe or socket is: -0.346546
aviavi@aviavi-VirtualBox:~/Desktop/os/Ex4$ make clean
rm -f mutex fctnl cond pipe *.txt 
aviavi@aviavi-VirtualBox:~/Desktop/os/Ex4$ 


