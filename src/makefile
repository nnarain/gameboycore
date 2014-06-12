
CC = gcc
CFLAGS = -g -Wall
INCLUDE_DIR = ../include
BIN_DIR = ../bin

APP_NAME = GBCoreTest

library:
	$(CC) -fpic -c GBEmulator.c
	$(CC) -shared -o libGBEmulator.so GBEmulator.o

test: test.o GBEmulator.o
	$(CC) -o $(APP_NAME) test.o GBEmulator.o
	mv *.o ../bin
	mv $(APP_NAME) $(BIN_DIR)

test.o:
	$(CC) -c $(CFLAGS) -I$(INCLUDE_DIR) test.c

GBEmulator.o:
	$(CC) -c $(CFLAGS) -I$(INCLUDE_DIR) GBEmulator.c

clean:
	@rm *.o
