
CC = g++
CFLAGS = -g -Wall -std=c++0x
INCLUDE_DIR = ../include

library:
	$(CC) -fpic -c GBEmulator.cpp
	$(CC) -shared -o libGBEmulator.so GBEmulator.o

test: Test.o GBEmulator.o
	$(CC) -o Test Test.o GBEmulator.o
	mv *.o ../bin

Test.o:
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) Test.cpp

GBEmulator.o:
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) GBEmulator.cpp
