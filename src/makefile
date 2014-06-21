
VERSION = 0.0.1

CC = gcc
CFLAGS = -g -Wall
INCLUDE_DIR = ../include
JAVA_INCLUDE = /usr/lib/jvm/java-7-openjdk-i386/include
BIN_DIR = ../bin

LIB_NAME = libGBCore

LD_FLAGS = -Wl,-R,-Wl,$(BIN_DIR)

APP_NAME = GBCoreTest

all: lib static_lib jni_lib

lib:
	$(CC) -fpic -c GBEmulator.c
	$(CC) -shared -o $(LIB_NAME).so GBEmulator.o
	mv $(LIB_NAME).so $(BIN_DIR)

static_lib:
	$(CC) -c $(CFLAGS) -DDEBUG GBEmulator.c
	ar rcs $(LIB_NAME).a GBEmulator.o
	mv $(LIB_NAME).a $(BIN_DIR)

jni_lib:
	$(CC) -fpic -c -I$(JAVA_INCLUDE) GBEmulator.c
	$(CC) -fpic -c -I$(JAVA_INCLUDE) GBCoreJNI.c
	$(CC) -shared -o $(LIB_NAME)-jni.so GBEmulator.o GBCoreJNI.o
	mv $(LIB_NAME)-jni.so $(BIN_DIR)
	mv *.o $(BIN_DIR)

test: test.o static_lib
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
