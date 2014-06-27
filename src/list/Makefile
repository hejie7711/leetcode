CC=gcc
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=

all: linked_list cyclic_sorted_list rotate

linked_list:
	$(CC) -o linked_list.o -c $(CFLAGS) $(CPPPATH) linked_list.c
	$(CC) -o linked_list linked_list.o $(LIBPATH) $(LIBS)

cyclic_sorted_list:
	$(CC) -o cyclic_sorted_list.o -c $(CFLAGS) $(CPPPATH) cyclic_sorted_list.c
	$(CC) -o cyclic_sorted_list cyclic_sorted_list.o $(LIBPATH) $(LIBS)

rotate:
	$(CC) -o rotate.o -c $(CFLAGS) $(CPPPATH) rotate.c
	$(CC) -o rotate rotate.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o linked_list cyclic_sorted_list rotate
