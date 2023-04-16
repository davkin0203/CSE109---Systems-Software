CC=gcc
CFLAGS=-g -c -Well -Wextra -Wwrite-strings
LFLAGS=-g

all: main.o libmylib.a
	${CC} -o main main.o -L src/ -l libmylib.a
main.o: main.c
	cpp main.c -I include > main.i
	cc -S main.i
	as main.s -o main.o
libmylib.a: mylib1.c mylib2.c
	cpp src/mylib1.c > mylib1.i
	cpp src/mylib2.c > mylib2.i
	cc -S mylib1.i
	cc -S mylib2.i
	as mylib1.s -o mylib1.o
	as mylib2.s -o mylib2.o
	ar rs libmylib.a mylib1.o mylib2.o
clean:
	rm -f *.i *.s *.a *.o main
