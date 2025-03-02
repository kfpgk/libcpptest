
# libcpptest

A C++ testing library.

## Table of Contents

- [libcpptest](#libcpptest)
	- [Table of Contents](#table-of-contents)
	- [Introduction](#introduction)
	- [Features](#features)
	- [Usage](#usage)
		- [Headers](#headers)
		- [Integration tests](#integration-tests)
			- [Single test case object](#single-test-case-object)
			- [Multi test case object.](#multi-test-case-object)
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
	- [Contribute](#contribute)
	- [License](#license)

## Introduction

This repository holds the source code, documentation and tests for the `C++` testing library `libcpptest`.

## Features

- Simple interface for creating and running tests
- Integration test templates
- Support for multiple test cases in one integration test object

## Usage

### Headers

The library provides the following headers.

```cpp
// libcpptest Exception class
#include <libcpptest/exception/Exception.hpp>

// Header for integration SingleTest class
#include <libcpptest/integration_test/SingleTest.hpp>

// Headers for integration MultiTest class
#include <libcpptest/integration_test/MultiTest.hpp>
#include <libcpptest/integration_test/TestCase.hpp>
```

### Integration tests

The library provides an <em>integration_test</em> package. This package is based on the <em>Template</em> design pattern and users should create their own integration test classes by deriving from either `SingleTest` or the `MultiTest` class.

By doing this, the written unit test will run inside a sandbox directory which gets cleaned up automatically after the test is finished.

#### Single test case object

For implementing a single test case integration test, create a class that derives from `SingleTest` and override the virtual methods `setup()`(optional), `perform()`(mandatory), `evaluate()`(mandatory) and `cleanUp()`(optional).

When invoking the `run()` command on an object that is a subtype of `SingleTest`, the previously described methods are called in the given order.

The complete example can be found in the <em>examples</em> sub directory.
```cpp
#include "FileReader.hpp"

#include <libcpptest/integration_test/SingleTest.hpp>
#include <libcpptest/exception/Exception.hpp>

#include <fstream>
#include <sstream>
#include <string>

class TestReadLineFromFile : public cpptest::integration_test::SingleTest {

public:
	explicit TestReadLineFromFile(const std::string& name) :
		SingleTest(name) { }

private:
	std::string content; ///< Data passed from perform() to evaluate()

	void setup() override {
		std::ofstream testFile("testfile");
		testFile << "This is some random content" << std::endl;
	}

	void perform() override {
		FileReader fileReader("testfile");
		content = fileReader.readLineFromFile();
	}

	void evaluate() override {
		if (content != "This is some random content") {
			std::stringstream message;
			message << "Content '" << content << "' does not match expectation";
			throw cpptest::exception::Exception(message.str());
		}
	}

	void cleanUp() override {
		/* Nothing to do, sandbox gets cleaned up by base class */
	}
};

int main(int argc, char* argv[]) {

	integration_test_single::TestReadLineFromFile test("Test read line from file");

	test.run();

	return 0;
}
```

#### Multi test case object.

For implementing an integration test that includes multiple test cases, inherit from `MultiTest`. Optionally override the `setup()` and `cleanUp()` methods. `perform()` and `evaluate()` methods are not available for multi test case objects. Instead create objects of type `Testcase` and add them to the integration test using `addTestCase()` inside the integration test class' constructor.

A `TestCase` object is defined by a `name`, a `perform()` function and a `evaluate()` function. Check out the examples for guidance.

The complete example can be found in the <em>examples</em> sub directory.
```cpp
#include "FileReader.hpp"

#include <libcpptest/integration_test/MultiTest.hpp>
#include <libcpptest/integration_test/TestCase.hpp>
#include <libcpptest/exception/Exception.hpp>

#include <fstream>
#include <functional>
#include <string>

class FileReaderTest : public MultiTest {

public:
	explicit FileReaderTest(const std::string& name) :
		MultiTest(name) {

		TestCase tc1{
			.name = "Read a line from file",
			.perform = std::bind(&FileReaderTest::performReadLine, this),
			.evaluate = std::bind(&FileReaderTest::evaluateReadLine, this)
		};
		addTestCase(tc1);

		TestCase tc2{
			.name = "Read from non existing file",
			.perform = std::bind(&FileReaderTest::performReadFromNonExisting, this),
			.evaluate = std::bind(&FileReaderTest::evaluateReadFromNonExisting, this)
		};
		addTestCase(tc2);
	}

private:
	std::string content; ///< Data passed from perform() to evaluate()
	bool exceptionThrown; ///< Pass flag whether exception occured to evaluate()

	void perform() override {
		FileReader fileReader("testfile");
		content = fileReader.readLineFromFile();
	}

	/**
	 * @brief Test case 1
	 */
	void performReadLine() {
		FileReader fileReader("testfile");
		content = fileReader.readLineFromFile();
	}

	void evaluateReadLine() const {
		if (content != "This is some random content") {
			std::stringstream message;
			message << "Content '" << content << "' does not match expectation";
			throw cpptest::exception::Exception(message.str());
		}
	}

	/**
	 * @brief Test case 2
	 */
	void performReadFromNonExisting() {
		exceptionThrown = false;
		try {
			FileReader fileReader("does-not-exist");
			content = fileReader.readLineFromFile();
		} catch (...) {
			exceptionThrown = true;
		}
	}

	void evaluateReadFromNonExisting() const {
		if (exceptionThrown == false) {
			std::stringstream message;
			message << "Expected an exception, but it did not occur.";
			throw cpptest::exception::Exception(message.str());
		}
	}

	void cleanUp() override {
		/* Nothing to do, sandbox gets cleaned up by base class */
	}

};

int main(int argc, char* argv[]) {
	
	integration_test_multi::FileReaderTest test("Test FileReader functionality");

	test.run();

	return 0;
}
```

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
cd libcpptest
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
+- libcpptest                # C++ testing library
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
|       +- *.test.cpp                   # Unit test source file
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

## Contribute

Check the following things when contributing to this library:

- [ ] UML diagrams affected by change and updated if necessary?
- [ ] Unit tests added? Unit tests executed (called in the corresponding unit test main() function)? 
- [ ] Unit tests run successfully?
- [ ] Is the public API of the library affected by the change?

## License

This project is licensed under the GNU GENERAL PUBLIC LICENSE - see the [LICENSE](LICENSE) file for details.