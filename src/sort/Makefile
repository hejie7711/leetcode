CC=g++
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=

all: radix_sort

radix_sort:
	$(CC) -o quick_sort.o -c $(CFLAGS) $(CPPPATH) quick_sort.cpp
	$(CC) -o radix_sort.o -c $(CFLAGS) $(CPPPATH) radix_sort.cpp
	$(CC) -o radix_sort quick_sort.o radix_sort.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o radix_sort
