G = g++
GFLAG = -Wall -g -std=c++11

all: main

main: main.o binfunc.o
	$(G) $(GFLAG) main.o binfunc.o -o main

main.o: main.cpp header.h
	$(G) $(GFLAG) -c main.cpp

binfunc.o: binfunc.cpp header.h
	$(G) $(GFLAG) -c binfunc.cpp

clean:
	rm -f *.o main
cleanall:
	rm *.o *.cpp main
