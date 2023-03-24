CC=gcc
CFLAGS=-std=c11 -Wall -g -O
LDLIBS=-lm

all:  auxiliary

auxiliary.o: utilities/xfunctions.h utilities/xfunctions.c utilities/utility.h utilities/utility.c auxiliary.c
	gcc -std=c11 -Wall -g -c -O utilities/xfunctions.c utilities/xfunctions.h utilities/utility.h utilities/utility.c auxiliary.c

xfunctions.o: utilities/xfunctions.c utilities/xfunctions.h
	gcc -std=c11 -Wall -g -c -O utilities/xfunctions.c

utility.o: utilities/utility.c utilities/utility.h
	gcc -std=c11 -Wall -g -c -O utilities/utility.c

auxiliary: auxiliary.o xfunctions.o utility.o
	gcc xfunctions.o utility.o auxiliary.o -lm -o auxiliary

clean:
	rm *.o auxiliary
