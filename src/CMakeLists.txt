
#
# GameBoy Core Emulation Library
#
# @author Natesh Narain
#

cmake_minimum_required(VERSION 2.6)

project("GameBoyCore")

# set library names
set(libNameShared gbcore)
set(libNameStatic gbcore-a)
set(libNameJNI gbcore-jni)

# set directory names
set(build "../build/")
set(buildObj "../build/lib/")

# create needed direcotries
file(MAKE_DIRECTORY ${build})
file(MAKE_DIRECTORY ${buildObj})

# set project directories
set(include "../include/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${buildObj})

include_directories(${include})
include_directories($ENV{JAVA_HOME}/include)
include_directories($ENV{JAVA_HOME}/include/win32)

# build core shared library
add_library(
	${libNameShared}
	SHARED
	GBEmulator.c
)

# build core static library
add_library(
	${libNameStatic}
	STATIC
	GBEmulator.c
)

# build jni shared library
add_library(
	${libNameJNI}
	SHARED
	GBCoreJNI.c
	GBEmulator.c
)




