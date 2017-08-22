# Gameboy Core

[![Build Status](https://travis-ci.org/nnarain/gameboycore.svg?branch=develop)](https://travis-ci.org/nnarain/gameboycore)
[![Build status](https://ci.appveyor.com/api/projects/status/jkrjhds3i67o5k76/branch/develop?svg=true)](https://ci.appveyor.com/project/nnarain/gameboycore/branch/develop)
[![GitHub issues](https://img.shields.io/github/issues/nnarain/gameboycore.svg)](https://github.com/nnarain/gameboycore/issues)
[![GitHub release](https://img.shields.io/github/release/nnarain/gameboycore.svg)](https://github.com/nnarain/gameboycore/releases)

GameboyCore is a Gameboy/Gameboy Color emulator library written in C++.

A library? Yes. This is a dependency free C++11 library. GameboyCore does not open a window to render frames, it does not collect user input or play audio. GameboyCore emulates the Gameboy system and provides the audio/video output through the GameboyCore API.

This means the emulation logic and GUI logic of an emulator are separate. As long as the target platform has a C++11 compiler that platform can run GameboyCore!

GameboyCore running as:
* [A desktop application](https://github.com/nnarain/dotrix)
* [A libretro core in RetroArch](https://github.com/nnarain/gameboycore-retro)
* [Python bindings, usable with pygame](https://github.com/nnarain/gameboycore-python)
* [An Android App](https://github.com/nnarain/dotrix-android)
* And possible WebAssembly!

The above application are somewhat incomplete however they all demonstrate GameboyCore working for the given environment.

Examples
--------

The GameboyCore repo includes an [example project](https://github.com/nnarain/gameboycore/tree/master/src/example).

Build
-----

**Build Options**

* `BUILD_DOCS`
* `BUILD_EXAMPLE`
* `BUILD_TESTS`

~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
cd path/to/project/
mkdir build && cd build
cmake .. -DBUILD_EXAMPLE="<ON/OFF>"
make
~~~~~~~~~~~~~~~~~~~~~~~~~~

Note: Building the example required SFML to be findable by CMake.
