#ifndef INTEGRATION_TEST_MULTI_FILE_READER_TEST_HPP
#define INTEGRATION_TEST_MULTI_FILE_READER_TEST_HPP

#include <libcpptest/integration_test/MultiTest.hpp>

#include <string>

namespace integration_test_multi {

	using namespace cpptest::integration_test;

	/**
	 * @brief This is the integration test class
	 * for the FileReader functionality
	 *
	 * This serves as an example for the libcpptest
	 * MultiTest class usage.
	 */
	class FileReaderTest : public MultiTest {

	public:
		/**
		 * @brief Constructor
		 * 
		 * @param[in] name The name of the test used for logging
		 */
		explicit FileReaderTest(const std::string& name);

	private:
		std::string content; ///< Data passed from perform() to evaluate()
		bool exceptionThrown; ///< Pass flag whether exception occured to evaluate()

		/**
		 * @brief General setup for all test cases
		 */
		void setup() override;

		/**
		 * @brief Test reading a line
		 */
		void performReadLine();
		void evaluateReadLine() const;

		/**
		 * @brief Test reading from non existing file
		 */
		void performReadFromNonExisting();
		void evaluateReadFromNonExisting() const;

		/**
		 * @brief Custom clean up for all test cases
		 */
		void cleanUp() override;

	};

}

#endif