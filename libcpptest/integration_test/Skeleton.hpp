#ifndef LIBCPPTEST_INTEGRATION_TEST_SKELETON_HPP
#define LIBCPPTEST_INTEGRATION_TEST_SKELETON_HPP

#include <libcpptest/integration_test/TestCase.hpp>

#include <libcpplog/logger/Log.hpp>

#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace cpptest::integration_test {

    /**
     * @brief Base class for integration tests
     * 
     * Provides a temporary sandbox for the 
     * derived class in `setup()` and deletes
     * the sandbox upon `cleanUp()` or destruction
     * of the object.
     * 
     * This class is incomplete and only defines
     * setup and cleanup, but leaves test execution
     * and evaluation up to specializations. Dervied
     * classes define this via overriding `doRun()`.
     * 
     * Patterns:
     *  - Template
     *  - Non virtual interface
     */
    class Skeleton {

    public:
        /**
         * @brief Destructor
         */
        virtual ~Skeleton() = default;

        /**
         * @brief Copy constructor (deleted)
         */
        Skeleton(const Skeleton&) = delete;

        /**
         * @brief Copy assignment operator (deleted)
         */
        Skeleton& operator=(const Skeleton& rhs) = delete;

        /**
         * @brief Set behavior when a fail is encountered in `run()` method.
         * 
         * @param value Set to true to exit on fail and set to false to return false on first fail
         */
        void setExitOnFail(bool value) noexcept;

        /**
         * @brief Set whether sandbox shall be cleaned up  after running this test.
         * 
         * Useful to set to true when debugging tests.
         * 
         * @param[in] value Set to true to keep sandbox
         */
        void setKeepSandBox(bool value) noexcept;

        /**
         * @brief Set whether previous sandbox gets cleaned up before running this test.
         *
         * @param[in] value Set to true to keep previous sandbox
         */
        void setKeepPreviousSandBox(bool value) noexcept;

        /**
         * @brief Set overall cleanup behavior
         * 
         * Set to true to disable any type of clean up.
         * Both sandbox cleanup & overriden `cleanUp()`
         * will not be performed.
         */
        void setSkipCleanUp(bool value) noexcept;

        /**
         * @brief Run this test
         */
        bool run();

    protected:
        /**
         * @brief Constructor
         *
         * Protected constructor, as this class serves only as a
         * base for concrete test classes.
         *
         * @param[in] name Name of the test as is displayed in logs
         * @param[in] logger A custom logger to be used for all outputs
         * 
         * @details
         * This constructor gets called also, when there is no logger object
         * provided by the caller. In this case the global logger object
         * from `libcpplog` gets used.
         */
        Skeleton(std::string name, cpplog::logger::Logger& logger = cpplog::logger::logger);

        /**
         * @brief Constructor
         *
         * Protected constructor, as this class serves only as a
         * base for concrete test classes.
         * 
         * @param[in] name Name of the test as is displayed in logs
         * @param[in] logger A custom logger to be used for all outputs
         */
        Skeleton(std::string name, const cpplog::logger::Logger& logger);

        /// @brief The logger to be used for all outputs including test results
        cpplog::logger::Logger& logger;

    private:
        const std::string name; ///< Name of the test

        /// @brief internal Logger in case none is provided by client
        std::optional<cpplog::logger::Logger> internalLogger;

        bool exitOnFail = true; ///< Exit if test fails
        bool keepSandBox = false; ///< Skip clean up of the sandbox
        bool keepPreviousSandBox = false; ///< Skip clean up of previous sandbox
        /// @brief Skip entire clean up of sandbox and prevent test specific clean up call
        bool skipCleanUp = false; 

        ///< Remember if clean up has been called to prevent calling it twice 
        ///< (e.g. in exception handler)
        bool cleanUpCalled = false;

        /**
         * @brief Wrap the virtual `setup()` method
         * inside sandbox setup and logging.
         */
        void wrapSetup();

        /**
         * @brief Wrap the virtual `cleanUp()` method
         * inside sandbox cleanup and logging.
         */
        void wrapCleanUp();

        /**
         * @brief Test specific setup method to be
         * overriden by concrete test class
         * 
         * Called before executing any test cases
         */
        virtual void setup();

        /**
         * @brief Template method to define test execution
         * 
         * Implement this to define how tests shall be executed
         */
        virtual void doRun() = 0;

        /**
         * @brief Test specific clean up method to be
         * overriden by concrete test class
         * 
         * Called after executing all (or up to first failing)
         * test cases
         */
        virtual void cleanUp();

        /**
         * @brief Defines behavior that is being performed on a failed test
         * 
         * Exits program if corresponding flag is set
         */
        void handleFailAndMaybeExit();

    };

}

#endif