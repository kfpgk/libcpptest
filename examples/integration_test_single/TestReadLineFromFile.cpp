#include <integration_test_single/TestReadLineFromFile.hpp>
#include <integration_test_single/FileReader.hpp>

#include <libcpptest/integration_test/TestCase.hpp>
#include <libcpptest/exception/Exception.hpp>

#include <fstream>
#include <functional>
#include <string>

namespace integration_test_single {

	using namespace cpptest::integration_test;

	TestReadLineFromFile::TestReadLineFromFile(const std::string& name) :
		SingleTest(name) {

	}

	void TestReadLineFromFile::setup() {
		std::ofstream testFile("testfile");
		testFile << "This is some random content" << std::endl;
	}

	void TestReadLineFromFile::perform() {
		FileReader fileReader("testfile");
		content = fileReader.readLineFromFile();
	}

	void TestReadLineFromFile::evaluate() {
		if (content != "This is some random content") {
			std::stringstream message;
			message << "Content '" << content << "' does not match expectation";
			throw cpptest::exception::Exception(message.str());
		}
	}

	void TestReadLineFromFile::cleanUp() {
		/* Nothing to do, sandbox gets cleaned up by base class */
	}

}