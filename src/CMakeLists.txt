
#
# Z80 Core Emulation Library
#
# @author Natesh Narain
#

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(appName GBCore)
SET(include "../include")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")

PROJECT(${appName})

INCLUDE_DIRECTORIES(${include})

ADD_LIBRARY(
	${appName}
	GBEmulator.cpp
)




