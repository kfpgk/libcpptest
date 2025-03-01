#include <integration_test_multi/FileReaderTest.hpp>
#include <integration_test_multi/FileReader.hpp>

#include <libcpptest/integration_test/TestCase.hpp>
#include <libcpptest/exception/Exception.hpp>

#include <fstream>
#include <functional>
#include <string>

namespace integration_test_multi {

	using namespace cpptest::integration_test;

	FileReaderTest::FileReaderTest(const std::string& name) :
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

	void FileReaderTest::setup() {
		std::ofstream testFile("testfile");
		testFile << "This is some random content" << std::endl;
	}

	void FileReaderTest::performReadLine() {
		FileReader fileReader("testfile");
		content = fileReader.readLineFromFile();
	}

	void FileReaderTest::evaluateReadLine() const {
		if (content != "This is some random content") {
			std::stringstream message;
			message << "Content '" << content << "' does not match expectation";
			throw cpptest::exception::Exception(message.str());
		}
	}

	void FileReaderTest::performReadFromNonExisting() {
		exceptionThrown = false;
		try {
			FileReader fileReader("does-not-exist");
			content = fileReader.readLineFromFile();
		} catch (...) {
			exceptionThrown = true;
		}
	}

	void FileReaderTest::evaluateReadFromNonExisting() const {
		if (exceptionThrown == false) {
			std::stringstream message;
			message << "Expected an exception, but it did not occur.";
			throw cpptest::exception::Exception(message.str());
		}
	}

	void FileReaderTest::cleanUp() {
		/* Nothing to do, sandbox gets cleaned up by base class */
	}

}