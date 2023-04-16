CC = gcc
CFLAGS =-g -c -Wall -Wextra -Wwrite-strings
LFLAGS =-g

which: which.o wrappers.o
	${CC} ${LFLAGS} -o which wrappers.o which.o

which.o: which.c wrappers.c
	${CC} ${CFLAGS} -c which.c

wrappers.o: wrappers.c
	${CC} ${CFLAGS} -c wrappers.c

clean:
	rm -f *.o which
