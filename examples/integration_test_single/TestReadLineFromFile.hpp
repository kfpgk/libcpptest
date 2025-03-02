#ifndef INTEGRATION_TEST_SINGLE_TEST_READ_LINE_FROM_FILE_HPP
#define INTEGRATION_TEST_SINGLE_TEST_READ_LINE_FROM_FILE_HPP

#include <libcpptest/integration_test/SingleTest.hpp>

#include <string>

namespace integration_test_single {

	using namespace cpptest::integration_test;

	/**
	 * @brief This is the integration test class
	 * to test read line from file via FileReader
	 * class
	 *
	 * This serves as an example for the libcpptest
	 * SingleTest class usage.
	 */
	class TestReadLineFromFile : public SingleTest {

	public:
		/**
		 * @brief Constructor
		 * 
		 * @param[in] name The name of the test used for logging
		 */
		explicit TestReadLineFromFile(const std::string& name);

	private:
		std::string content; ///< Data passed from perform() to evaluate()

		/**
		 * @brief General setup for all test cases
		 */
		void setup() override;

		/**
		 * @brief Perform the test
		 */
		void perform() override;

		/**
		 * @brief Evaluate test results
		 */
		void evaluate() override;

		/**
		 * @brief Custom clean up for all test cases
		 */
		void cleanUp() override;

	};

}

#endif