#ifndef LIBCPPTEST_INTEGRATION_TEST_TEST_CASE_HPP
#define LIBCPPTEST_INTEGRATION_TEST_TEST_CASE_HPP

#include <functional>
#include <string>

namespace cpptest::integration_test {

    /**
     * @brief A struct holding a testcase, which
     * consists of a `perform()` and `evaluate()`
     * function. 
     * 
     * This test case can be added to a `MultiTest`
     * object and is being performed upon the
     * `MultiTest`s `run()` invokation.
     */
    struct TestCase {
        std::string name; ///< The name of the test case
        std::function<void(void)> perform; ///< The perform test function
        std::function<void(void)> evaluate; ///< The evaluate test function
    };
}

#endif