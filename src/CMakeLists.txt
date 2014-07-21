
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
set(buildLib "../build/lib/")
set(buildObj "../build/lib/")

# create needed direcotries
file(MAKE_DIRECTORY ${build})
file(MAKE_DIRECTORY ${buildLib})

# set project directories
set(include "../include/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${buildObj})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${buildLib})

include_directories(${include})
include_directories($ENV{JAVA_HOME}/include)
include_directories($ENV{JAVA_HOME}/include/win32)

include_directories(/opt/sdl/include)

link_directories(/opt/sdl)

# build core shared library
add_library(
	${libNameShared}
	SHARED
	gbapi.c
	add.c
	decrement_reg_pair.c
	increment.c
	decrement.c
	exchange.c
	load.c
	subtract.c
	increment_reg_pair.c
	special_accumulator_flag.c
	nop.c
	opts.c
	logic.c
	double_add.c
	stack.c
	branch.c
	shift.c
	rotate.c
	compare.c
	gbmapregion.c
	gbtile.c
	gbpalette.c
)

# build core static library
add_library(
	${libNameStatic}
	STATIC
	gbapi.c
	add.c
	decrement_reg_pair.c
	increment.c
	decrement.c
	exchange.c
	load.c
	subtract.c
	increment_reg_pair.c
	special_accumulator_flag.c
	nop.c
	opts.c
	logic.c
	double_add.c
	stack.c
	branch.c
	shift.c
	rotate.c
	compare.c
	gbmapregion.c
	gbtile.c
	gbpalette.c
)

# build jni shared library
add_library(
	${libNameJNI}
	SHARED
	gbcorejni.c
	gbparserjni.c
	gbapi.c
	gbparser.c
	add.c
	decrement_reg_pair.c
	increment.c
	decrement.c
	exchange.c
	load.c
	subtract.c
	increment_reg_pair.c
	special_accumulator_flag.c
	nop.c
	opts.c
	logic.c
	double_add.c
	stack.c
	branch.c
	shift.c
	rotate.c
	compare.c
	gbmapregion.c
	gbtile.c
	gbpalette.c
)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../build/test")
# add test executable
add_executable(
	GBTest
	test.c
	gbapi.c
	gbparser.c
	add.c
	decrement_reg_pair.c
	increment.c
	decrement.c
	exchange.c
	load.c
	subtract.c
	increment_reg_pair.c
	special_accumulator_flag.c
	nop.c
	opts.c
	logic.c
	double_add.c
	stack.c
	branch.c
	shift.c
	rotate.c
	compare.c
	gbmapregion.c
	gbtile.c
	gbpalette.c
)

target_link_libraries(GBTest SDL2-2.0)

