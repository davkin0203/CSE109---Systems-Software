CC=gcc
CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

filterFile: filterFile.o syscalls.o
	${CC} ${LFLAGS} filterFile.o syscalls.o -o filterFile

file.o: filterFile.c
	${CC} ${CFLAGS} filterFile.c 

file2.o: syscalls.c
	${CC} ${CFLAGS} syscalls.c

clean:
	rm -f *.o filterFile
