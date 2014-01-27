CC=g++
CFLAGS=-g -O2 -Wall -fPIC -std=c++0x
CPPPATH=
LIBPATH=
LIBS=

all: clonegraph

clonegraph:
	$(CC) -o clonegraph.o -c $(CFLAGS) $(CPPPATH) clonegraph.cpp
	$(CC) -o clonegraph clonegraph.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o clonegraph
