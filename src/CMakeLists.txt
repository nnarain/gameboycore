
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

# set project directories
set(include "../include/")

include_directories(${include})
include_directories($ENV{JAVA_HOME}/include)
include_directories($ENV{JAVA_HOME}/include/win32)

# build core shared library
add_library(
	${libNameShared}
	SHARED
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
	mbc.c
)

# build core static library
add_library(
	${libNameStatic}
	STATIC
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
	mbc.c
)

# build jni shared library
add_library(
	${libNameJNI}
	SHARED
	gbcorejni.c
	gbparser.c
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
	mbc.c
)


