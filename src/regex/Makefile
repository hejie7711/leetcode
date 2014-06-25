CC=gcc
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=

all: regex

regex:
	$(CC) -o regex.o -c $(CFLAGS) $(CPPPATH) regex.c
	$(CC) -o regex regex.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o regex
