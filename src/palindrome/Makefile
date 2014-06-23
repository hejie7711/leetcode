CC=g++
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=

all: palin_str palin_num

palin_str:
	$(CC) -o palin_str.o -c $(CFLAGS) $(CPPPATH) palin_str.cpp
	$(CC) -o palin_str palin_str.o $(LIBPATH) $(LIBS)

palin_num:
	$(CC) -o palin_num.o -c $(CFLAGS) $(CPPPATH) palin_num.cpp
	$(CC) -o palin_num palin_num.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o palin_str palin_num
