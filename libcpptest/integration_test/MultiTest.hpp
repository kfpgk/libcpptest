#ifndef LIBCPPTEST_INTEGRATION_TEST_MULTI_TEST_HPP
#define LIBCPPTEST_INTEGRATION_TEST_MULTI_TEST_HPP

#include <libcpptest/integration_test/Skeleton.hpp>
#include <libcpptest/integration_test/TestCase.hpp>

#include <libcpplog/logger/Logger.hpp>

#include <vector>

namespace cpptest::integration_test {

    /**
     * @brief Multiple test case integration test
     * 
     * User can add test cases via the `addTestCase()`
     * method.
     * User may override `setup()` and `cleanUp()`
     * methods.
     * 
     * Upon calling `run()` the following methods
     * get executed in this order:
     *  - `setup()`
     *  - `perform()` and `evaluate()` for each test case
     *  - `cleanUp()`
     * 
     * Provides a temporary sandbox for the 
     * derived class in `setup()` and deletes
     * the sandbox upon `cleanUp()` or destruction
     * of the object.
     * 
     * Patterns:
     *  - Template
     *  - Non virtual interface
     */
    class MultiTest : public Skeleton {

    public:
        /**
         * @brief Default destructor
         */
        virtual ~MultiTest() = default;

        /**
         * @brief Deleted copy constructor
         */
        MultiTest(const MultiTest&) = delete;

        /**
         * @brief Deleted copy assignment operator
         */
        MultiTest& operator==(const MultiTest& rhs) = delete;

    protected:
        /**
         * @brief Constructor
         *
         * Protected constructor, as this class serves only as a
         * base for concrete test classes.
         *
         * @param[in] name Name of the test as is displayed in logs
         */
        explicit MultiTest(const std::string& name);

        /**
         * @brief Constructor
         *
         * Protected constructor, as this class serves only as a
         * base for concrete test classes.
         *
         * @param[in] name Name of the test as is displayed in logs
         * @param[in] logger A custom logger to be used for all outputs
         */
        MultiTest(const std::string& name, const cpplog::logger::Logger& logger);

        /**
         * @brief Constructor
         *
         * Protected constructor, as this class serves only as a
         * base for concrete test classes.
         *
         * @param[in] name Name of the test as is displayed in logs
         * @param[in] logger A custom logger to be used for all outputs
         */
        MultiTest(const std::string& name, cpplog::logger::Logger& logger);
        
        /**
         * @brief add a test case that will be executed upon a 
         * call to `run()`
         */
        void addTestCase(TestCase testCase);

    private:
        std::vector<TestCase> testCases; ///< Collection of test cases

        /**
         * @brief Wrap a call to a test case execution
         */
        void wrapPerform(const TestCase& testCase);

        /**
         * @brief Wrap a call to test case evaluation
         */
        void wrapEvaluate(const TestCase& testCase);

        /**
         * @brief Perform procedure to run a collection of test cases
         */
        void doRun() final;
    };

}

#endif