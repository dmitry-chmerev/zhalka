INCLUDES=-I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -L /usr/lib/gcc/x86_64-linux-gnu/11
CC=clang++ ${INCLUDES} -g
libsdl.a: window.cpp renderer.cpp exception.cpp
	${CC} -c window.cpp -o window.o
	${CC} -c renderer.cpp -o renderer.o
	${CC} -c exception.cpp -o exception.o
	ar -crs libsdl.a window.o renderer.o exception.o
