GameBoy Core
============

Overview
--------

Implement the core instructions of the hybrid Z80/8080 processor inside the Gameboy.

Installation
------------

**Environment Variables**

JAVA_HOME must be set in your environment.

**Clone Git repository**
```bash
$ git clone https://nnarain@bitbucket.org/nnarain/gameboycore.git
$ cd path/to/gameboycore
```

**Build C sources with CMake.**

Create a directory for CMake output.

```bash
$ mkdir unixmake
$ cd unixmake
```

Use cmake command to generate you make\project files (ex. Unix Makefiles)

```bash
$ cmake -G "Unix Makefiles" ../src
```

Build source with your project\make files

```bash
$ make
```

Shared libraries will be placed in build/lib

**Build Java Sources with Apache ANT**

```bash
$ cd path/to/gameboycore
$ ant
```