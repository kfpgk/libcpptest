
# libcpptest

A C++ testing library.

## Table of Contents

- [libcpptest](#libcpptest)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Features](#features)
  - [Usage](#usage)
  - [Dependencies](#dependencies)
  - [Build](#build)
    - [Library](#library)
    - [Tests](#tests)
    - [Debug build](#debug-build)
  - [Installation](#installation)
    - [Windows](#windows)
      - [Static release version](#static-release-version)
      - [Static debug version](#static-debug-version)
  - [Directory structure](#directory-structure)
  - [License](#license)

## Introduction

This repository holds the source code, documentation and tests for the `C++` testing library `libcpptest`.

## Features

- Simple interface for creating and running tests
- Integration test templates
- Support for multiple test cases in one integration test object

## Usage

## Dependencies

- <em>C++23</em>.
- [libcpplog](https://github.com/kfpgk/libcpplog)

## Build

### Library

Build the library:
```shell
cd libcpptest
mkdir -p build/release
cd build/release
cmake ../..
cmake --build .
```

### Tests

Set the `BUILD_UNIT_TESTS` option to build unit tests.

```shell
cd libcpptest
mkdir -p build/release
cd build/release
cmake -DBUILD_UNIT_TESTS=ON ../..
cmake --build .
```

Run the tests using `ctest`
```shell
make test
```

Unit test names are preceded by `UT` in the result view.

### Debug build

Use the `CMAKE_BUILD_TYPE` option to enable debug build.

```shell
cd libcpplog
mkdir -p build/debug
cd build/debug
cmake -DCMAKE_BUILD_TYPE=DEBUG ../..
cmake --build .
```

## Installation

To install the library, follow these steps:

Building a static library is the default.
For building shared libraries use the <em>cmake</em> option `BUILD_SHARED_LIBS`. Examples see below.

### Windows

<b>MSVC</b> requires dependencies to be the same type of build as the actual target executable. 
This is why it makes sense to provide both a release build as well as a debug build library.
We achieve this by adding a `d` postfix to the library name (`libcpptestd.lib`), when performing a debug build.
This way we can install both versions of the library next to each other. The recommendation is to <b>install both</b>
[release](#windows-static-release-install) and [debug](#windows-static-debug-install) versions, so the client 
can link to whichever build it needs.

<a id="windows-static-release-install"></a>
#### Static release version
Install instructions for the static release version using `powershell`.
Use `-DCMAKE_INSTALL_PREFIX` only if you do not want to install to the default location.

```powershell
Set-Location -path libcpptest
New-Item -name build\release -ItemType Directory -Force
Set-Location build\release
cmake ..\.. -DCMAKE_INSTALL_PREFIX=<absolute-path-to-installation-dir>
cmake --build . --config Release
```
Installation may require admin privileges depending on install location. If so use a <em>administrator</em> `powershell` or `cmd` for the install command.

```powershell
cmake --build . --target install --config Release
```

<a id="windows-static-debug-install"></a>
#### Static debug version
Install instructions for the static debug version using `powershell`.
Use `-DCMAKE_INSTALL_PREFIX` only if you do not want to install to the default location.

```powershell
Set-Location -path libcpptest
New-Item -name build\debug -ItemType Directory -Force
Set-Location build\debug
cmake ..\.. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=<absolute-path-to-installation-dir>
cmake --build . --config Debug
```
Installation may require admin privileges depending on install location. If so use a <em>administrator</em> `powershell` or `cmd` for the install command.

```powershell
cmake --build . --target install --config Debug
```

<a id="directory-structure"></a>
## Directory structure

<pre>
(root)
+- examples                 # Examples using libcpptest
|   +- <em>example1</em>
|       +- CMakeLists.txt
|       +- *.cpp
+- libcpplog                # C++ testing library
|   +- doc
|       +- *.puml           # UML diagram 
|   +- CMakeLists.txt
|   +- *.cpp
|   +- *.hpp
|   +- <em>component1</em>                       # C++ testing library component sub directory
|       +- doc
|           +- *.puml                   # UML diagram
|       +- CMakeLists.txt
|       +- *.cpp                        # Library source file
|       +- *.hpp                        # Library header file
|       +- *.tpp                        # Library template implementation file
|       +- *.test.cpp                   # Unit tests source file
|       +- *.test.hpp                   # Unit test header file
|   +- <em>component2</em>                       # C++ testing library component sub directory
|       +- doc
|           +- *.puml                   
|       +- CMakeLists.txt
|       +- *.cpp
|       +- *.hpp
|       +- *.test.cpp
|       +- *.test.hpp
+- CMakeLists.txt
</pre>

## License

This project is licensed under the GNU GENERAL PUBLIC LICENSE - see the [LICENSE](LICENSE) file for details.