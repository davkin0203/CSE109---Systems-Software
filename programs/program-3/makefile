R_DIRECTORY = build/lib/release/
O_DIRECTORY = build/objects/
D_DIRECTORY = build/lib/debug/
M_DIRECTORY = usr/lib/
T_DIRECTORY = build/bin/
WFLAGS = -g -Wall -Wextra -Wwrite-strings

all: static shared tests install debug clean

static: ${R_DIRECTORY}liblinkedlist.a ${R_DIRECTORY}libhashset.a
${R_DIRECTORY}libhashset.a: ${O_DIRECTORY}lib.o
	mkdir -p ${R_DIRECTORY}
	ar rcs ${R_DIRECTORY}libhashset.a ${O_DIRECTORY}lib.o

${R_DIRECTORY}liblinkedlist.a: ${O_DIRECTORY}LinkedList.o
	mkdir -p ${R_DIRECTORY}
	ar rcs ${R_DIRECTORY}liblinkedlist.a ${O_DIRECTORY}LinkedList.o

${O_DIRECTORY}lib.o: src/libhs.cpp include/hashset.hpp include/LinkedList.h
	g++ -fPIC -c ${WFLAGS} -Iinclude src/libhs.cpp -o ${O_DIRECTORY}lib.o

${O_DIRECTORY}LinkedList.o: src/libll.c include/LinkedList.h
	g++ -fPIC -c ${WFLAGS} -Iinclude src/libll.c -o ${O_DIRECTORY}LinkedList.o

shared: ${R_DIRECTORY}libhashset.so
${R_DIRECTORY}libhashset.so: ${O_DIRECTORY}lib.o ${O_DIRECTORY}LinkedList.o
	mkdir -p ${R_DIRECTORY}
	g++ -g -shared -o ${R_DIRECTORY}libhashset.so ${O_DIRECTORY}lib.o ${O_DIRECTORY}LinkedList.o

debug: ${D_DIRECTORY}debug.so
${D_DIRECTORY}debug.so: ${O_DIRECTORY}test.o ${O_DIRECTORY}lib.o ${O_DIRECTORY}LinkedList.o
	mkdir -p ${D_DIRECTORY}
	g++ -shared -g -o ${D_DIRECTORY}debug.so ${O_DIRECTORY}test.o ${O_DIRECTORY}lib.o ${O_DIRECTORY}LinkedList.o

install:
	mkdir -p ${M_DIRECTORY}
	mv ${R_DIRECTORY}libhashset.so ${M_DIRECTORY}

tests: ${T_DIRECTORY}tests
${T_DIRECTORY}tests: ${O_DIRECTORY}test.o ${R_DIRECTORY}libhashset.so
	mkdir -p ${T_DIRECTORY}
	g++ ${O_DIRECTORY}test.o -L${R_DIRECTORY} -lhashset -Wl,-Bsymbolic,-rpath=${R_DIRECTORY} -o ${T_DIRECTORY}tests
	${T_DIRECTORY}tests

${O_DIRECTORY}test.o: test/test.cpp include/hashset.hpp
	g++ -fPIC -c ${WFLAGS} -Iinclude test/test.cpp -o ${O_DIRECTORY}test.o

clean:
	rm -f ${D_DIRECTORY}debug.so
	rm -f ${R_DIRECTORY}libhashset.so
	rm -f ${O_DIRECTORY}LinkedList.o
	rm -f ${O_DIRECTORY}lib.o
	rm -f ${R_DIRECTORY}liblinkedlist.a 
	rm -f ${R_DIRECTORY}libhashset.a
	rm -f ${O_DIRECTORY}test.o
	rm -f ${R_DIRECTORY}libonelib.a
	rm -f ${T_DIRECTORY}tests


        ### REQURIED TARGETS ###

# X - all - build static and shared libraries.

# X - static - build a static library `libhashset.a`, put it in `build/lib/release`. Put object files in `build/objects`

# X - shared - build a shared library `libhashset.so`, put it in `build/lib/release`. Put object files in `build/objects`

# X - debug - build a shared library with debug symbols, put it in `build/lib/debug`. Put object files in `build/objects`

# X - clean - remove all build artifacts by removing the build directory.

# X - install - move the shared library to `/usr/lib`

# X - test - compile `test/test.cpp` and run it. Put the tests executable in `build/bin`. Put object files in `build/objects`


# ${R_DIRECTORY}libonelib.a: ${O_DIRECTORY}lib.o ${O_DIRECTORY}LinkedList.o
# 	mkdir -p ${R_DIRECTORY}
# 	ar rcs ${R_DIRECTORY}libonelib.a ${O_DIRECTORY}LinkedList.o ${O_DIRECTORY}lib.o
