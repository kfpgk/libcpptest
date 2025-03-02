#include <integration_test_single/FileReader.hpp>

#include <fstream>
#include <string>
#include <string_view>

namespace integration_test_single {

	FileReader::FileReader(const std::string_view fileName) :
		fileName{ fileName } {

	}

	std::string FileReader::readLineFromFile() const {
		std::ifstream os(fileName);
		if (!os.is_open()) {
			throw "Could not open file";
		}
		std::string line;
		std::getline(os, line);
		return line;
	}

}