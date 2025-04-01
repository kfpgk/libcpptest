#ifndef LIBCPPTEST_INTEGRATION_TEST_FAIL_HPP
#define LIBCPPTEST_INTEGRATION_TEST_FAIL_HPP

#include <stdexcept>
#include <string>

namespace cpptest::integration_test {

    /**
     * @brief Exception representing a Fail result
     * 
     * Throw this exception to indicate a failed test
     */
    class Fail : public std::logic_error {

    public:
        /**
         * @brief Constructor
         * 
         * @param[in] message The message to be logged
         */
        explicit Fail(std::string message);

    };

}

#endif