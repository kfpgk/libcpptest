#ifndef LIBCPPTEST_INTEGRATION_TEST_MULTI_TEST_TEST_HPP
#define LIBCPPTEST_INTEGRATION_TEST_MULTI_TEST_TEST_HPP

namespace cpptest::integration_test::unit_test {

    /**
     * @brief Unit test for MultiTest
     */
    class MultiTestTest {

    public:
        /**
         * @brief Test behavior of `run()` invocation in case of no test cases
         */
        void noTestCasesAdded() const;

        /**
         * @brief Test scenario in which all test pass
         */
        void allPass() const;

        /**
         * @brief Test scenario in which the first test case fails
         */
        void firstFails() const;
        
        /**
         * @brief Test scenario in which the second test case fails
         */
        void secondFails() const;

    };

}

#endif