CC = gcc
AR = ar
FLAGS = -Wall -g

.PHONY: clean all run

all: mutex fncl cond pipe
run: mutex fncl cond pipe ./mutex ./fctnl ./cond ./pipe
	
mutex: mymutex.c
	$(CC) -pthread -o mutex mymutex.c
	
fncl: myfctnl.c
	$(CC) -pthread -o fctnl myfctnl.c
	
cond: mycond.c
	$(CC) -pthread -o cond mycond.c
	
pipe: mypipe.c
	$(CC) -pthread -o pipe mypipe.c

clean:
	rm -f mutex fctnl cond pipe *.txt 
