#ifndef LIBCPPTEST_INTEGRATION_TEST_SINGLE_TEST_TEST_HPP
#define LIBCPPTEST_INTEGRATION_TEST_SINGLE_TEST_TEST_HPP

namespace cpptest::integration_test::unit_test {

    /**
     * @brief Unit test for SingleTest
     */
    class SingleTestTest {

    public:
        /**
         * @brief Test that all tempalte methods get called
         * and that `run()` returns true for a passing test
         */
        void passingTest() const;

        /**
         * @brief Test that all tempalte methods get called
         * and that `run()` returns false for a failing test
         */
        void failingTest() const;

    };

}

#endif