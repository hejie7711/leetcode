CC=gcc
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=

all: strtok strcpy

strtok:
	$(CC) -o strtok.o -c $(CFLAGS) $(CPPPATH) strtok.c
	$(CC) -o strtok strtok.o $(LIBPATH) $(LIBS)

strcpy:
	$(CC) -o strcpy.o -c $(CFLAGS) $(CPPPATH) strcpy.c
	$(CC) -o strcpy strcpy.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o strtok strcpy
