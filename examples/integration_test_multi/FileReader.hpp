#ifndef INTEGRATION_TEST_MULTI_FILE_READER_HPP
#define INTEGRATION_TEST_MULTI_FILE_READER_HPP

#include <string>
#include <string_view>

namespace integration_test_multi {

	/**
	 * @brief This class reads from a file
	 * 
	 * This serves as an example for the libcpptest
	 * MultiTest class usage.
	 */
	class FileReader {
	public:
		/**
		 * @brief Constructor
		 * 
		 * @param[in] fileName Path to the file which will be read
		 */
		FileReader(const std::string_view fileName);

		/**
		 * @brief Read a line from the file
		 */
		std::string readLineFromFile() const;

	private:
		std::string fileName; ///< File to be read
	};

}

#endif