# GameboyCore

[![Build Status](https://travis-ci.org/nnarain/gameboycore.svg?branch=develop)](https://travis-ci.org/nnarain/gameboycore)
[![Build status](https://ci.appveyor.com/api/projects/status/jkrjhds3i67o5k76/branch/develop?svg=true)](https://ci.appveyor.com/project/nnarain/gameboycore/branch/develop)
[![codecov](https://codecov.io/gh/nnarain/gameboycore/branch/master/graph/badge.svg)](https://codecov.io/gh/nnarain/gameboycore)
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

Building
--------

The `GameboyCore` library does not have any dependencies and can be compiled using any C++11 compiler. The tools contained in this repo, however, do have additional dependencies that need to be installed. All dependencies should be findable by CMake.

Fetch source:

```bash
git clone https://github.com/nnarain/gameboycore
cd gameboycore
git submodule update --init --recursive
```

To build the library, simply run `cmake`.

```bash
mkdir build && cd build
cmake ..
cmake --build . --target gameboycore
```

**Building Tests**

Install `gtest` and build with `BUILD_TESTS=ON`. Optionally you can setup benchmarks by installing `google-benchmark`.

```bash
cmake .. -DBUILD_TESTS=ON
cmake --build . --target check
cmake --build . --target bench
```

A few test ROMs can be run as well.

```bash
cmake --build . --target run_test_roms
```

**Building Tools**

Enable building tools by specifying `BUILD_TOOLS=ON`. If building tools is enabled, all will be built by default. Disable building tools with `WITH_<tool name>=OFF`.

All tools are compiled with the latest C++ standard.

Debugger:

* Used for running Gameboy ROMs and inspecting the core
* Depends on SFML

RomInfo

* Used for printing the information in the ROM header


