#ifndef LIBCPPTEST_INTEGRATION_TEST_SINGLE_TEST_HPP
#define LIBCPPTEST_INTEGRATION_TEST_SINGLE_TEST_HPP

#include <libcpptest/integration_test/Skeleton.hpp>

#include <libcpplog/logger/Logger.hpp>

#include <string>

namespace cpptest::integration_test {

    /**
     * @brief Single test case integration test
     * 
     * User must override `perform()` and `evaluate()`
     * methods.
     * User may override `setup()` and `cleanUp()`
     * methods.
     * 
     * Upon calling `run()` the following methods
     * get executed in this order:
     *  - `setup()`
     *  - `perform()`
     *  - `evaluate()`
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
    class SingleTest : public Skeleton {

    public:
        /**
         * @brief Default destructor 
         */
        virtual ~SingleTest() = default;

        /**
         * @brief Deleted copy constructor
         */
        SingleTest(const SingleTest&) = delete;

        /**
         * @brief Deleted copy assignment operator
         */
        SingleTest& operator==(const SingleTest& rhs) = delete;

    protected:
        /**
         * @brief Constructor
         *
         * Protected constructor, as this class serves only as a
         * base for concrete test classes.
         *
         * @param[in] name Name of the test as is displayed in logs
         */
        explicit SingleTest(const std::string& name);

        /**
         * @brief Constructor
         *
         * Protected constructor, as this class serves only as a
         * base for concrete test classes.
         *
         * @param[in] name Name of the test as is displayed in logs
         * @param[in] logger A custom logger to be used for all outputs
         */
        SingleTest(const std::string& name, const cpplog::logger::Logger& logger);

        /**
         * @brief Constructor
         *
         * Protected constructor, as this class serves only as a
         * base for concrete test classes.
         *
         * @param[in] name Name of the test as is displayed in logs
         * @param[in] logger A custom logger to be used for all outputs
         */
        SingleTest(const std::string& name, cpplog::logger::Logger& logger);        

    private:
        /**
         * @brief Wrap a call to the pure virtual `perform()` method
         */
        void wrapPerform();

        /**
         * @brief Wrap a call to the pure virtual `evaluate()` method
         */
        void wrapEvaluate();

        /**
         * @brief Pure virtual perform method
         * 
         * Override this to define the test case execution
         */
        virtual void perform() = 0;

        /**
         * @brief Pure virtual evaluate method
         * 
         * Override this to define the test case evaluation
         */
        virtual void evaluate() = 0;

        /**
         * @brief Perform procedure to run a single test case
         */
        void doRun() final;
    };

}

#endif