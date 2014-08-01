CC=gcc
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=

all: strtok

strtok:
	$(CC) -o strtok.o -c $(CFLAGS) $(CPPPATH) strtok.c
	$(CC) -o strtok strtok.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o strtok
