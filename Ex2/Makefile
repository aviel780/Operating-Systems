CC=gcc
FLAGS=-WALL -g

all: shell mytee mync

shell: shell.c
	$(CC) -o shell shell.c
mytee: mytee.c
	$(CC) -o mytee  mytee.c
mync: mync.c
	$(CC) -o mync mync.c
clean:
	rm -f shell mytee mync