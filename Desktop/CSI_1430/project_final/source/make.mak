CC = g++
CFLAGS = -g -Wall

default: main

main: main.o square.o types.o global.o
	$(CC) $(CFLAGS) -o main main.o square.o types.o global.o

main.o: main.cpp square.hpp
	$(CC) $(CFLAGS) -c main.cpp

square.o: square.cpp square.hpp types.hpp global.hpp
	$(CC) $(CFLAGS) -c square.cpp

types.o: types.cpp types.hpp
	$(CC) $(CFLAGS) -c types.cpp

global.o: global.cpp global.hpp
	$(CC) $(CFLAGS) -c global.cpp

clean:
	$(RM) main *.o *~
