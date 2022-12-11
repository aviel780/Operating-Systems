#!make -f
CC=gcc
FLAGS=-Wall -g

all: cmp copy codec1.so codec2.so encode decode

cmp: cmp.c
	gcc ${FLAGS} -o cmp cmp.c
copy: copy.c
	gcc ${FLAGS} -o copy copy.c
encode.o: encode.c codec.h
	gcc ${FLAGS} -c encode.c
decode.o: decode.c codec.h
	gcc ${FLAGS} -c decode.c
codec1.o: codec1.c codec.h
	gcc ${FLAGS} -c codec1.c
codec2.o: codec2.c codec.h
	gcc ${FLAGS} -c codec2.c
codec1.so: codec1.o
	gcc -shared -o codec1.so codec1.o
codec2.so: codec2.o
	gcc -shared -o codec2.so codec2.o
encode: encode.o codec1.so codec2.so
	gcc ${FLAGS} -o encode encode.o ./codec1.so ./codec2.so -lm -ldl
decode: decode.o codec1.so codec2.so
	gcc ${FLAGS} -o decode decode.o ./codec1.so ./codec2.so -lm -ldl

.PHONY: clean all

clean:
	rm -f decode encode copy cmp *.o *.so


