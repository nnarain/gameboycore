
CC = gcc
CFLAGS = -g -Wall
INCLUDE_DIR = ../include
BIN_DIR = ../bin

LIB_NAME = libGBCore

LD_FLAGS = -Wl,-R,-Wl,$(BIN_DIR)

APP_NAME = GBCoreTest

lib:
	$(CC) -fpic -c GBEmulator.c
	$(CC) -shared -o $(LIB_NAME).so GBEmulator.o
	mv $(LIB_NAME).so $(BIN_DIR)

static_lib:
	$(CC) -c $(CFLAGS) -DDEBUG GBEmulator.c
	ar rcs $(LIB_NAME).a GBEmulator.o
	mv $(LIB_NAME).a $(BIN_DIR)

test: test.o lib static_lib
	$(CC) -o $(APP_NAME) test.o -static -L$(BIN_DIR) -lGBCore
	mv *.o ../bin
	mv $(APP_NAME) $(BIN_DIR)

test.o:
	$(CC) -c $(CFLAGS) -DDEBUG test.c

GBEmulator.o:
	$(CC) -c $(CFLAGS) -DDEBUG GBEmulator.c

clean:
	@rm *.o
	@rm $(BIN_DIR)/*.o
