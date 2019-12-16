ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o shell.o pipe.o parse.o redirect.o
	$(CC) -o program main.o shell.o pipe.o parse.o redirect.o

main.o: main.c shell.h
	$(CC) -c main.c

shell.o: shell.c shell.h
	$(CC) -c shell.c
pipe.o:	pipe.c shell.h
	$(CC) -c pipe.c
parse.o:	parse.c shell.h
	$(CC) -c parse.c
redirect.o:	redirect.c shell.h
	$(CC) -c redirect.c
run:
	./program

memcheck:
	valgrind --leak-check:yes ./program

clean:
	rm *.o
	rm *~
