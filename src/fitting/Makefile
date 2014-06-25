CC=gcc
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=

all: fitting

fitting:
	$(CC) -o fitting.o -c $(CFLAGS) $(CPPPATH) fitting.c
	$(CC) -o fitting fitting.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o fitting
