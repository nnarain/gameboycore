
#
# Z80 Core Emulation Library
#
# @author Natesh Narain
#

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(appName Z80Core)
SET(include "../include")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")

PROJECT(${appName})

INCLUDE_DIRECTORIES(${include})

ADD_LIBRARY(
	${appName}
	Z80Emulator.cpp
)




