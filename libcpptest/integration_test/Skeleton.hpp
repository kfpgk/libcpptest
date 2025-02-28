#ifndef LIBCPPTEST_INTEGRATION_TEST_SKELETON_HPP
#define LIBCPPTEST_INTEGRATION_TEST_SKELETON_HPP

#include <libcpptest/integration_test/TestCase.hpp>

#include <libcpplog/logger/Logger.hpp>

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
     * class define this via overriding `doRun()`.
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
         * @brief Set behavior when a fail is encountered
         * in `run()` method.
         * 
         * -  true: exit fail
         * - false: return `false` on first fail
         */
        void setExitOnFail(bool value) noexcept;

        /**
         * @brief Set whether sandbox shall be cleaned up 
         * after running this test.
         * 
         * Useful to set to true when debugging tests.
         */
        void setKeepSandBox(bool value) noexcept;

        /**
         * @brief Set whether previous sandbox gets cleaned up
         * before running this test.
         */
        void setKeepOldSandBox(bool value) noexcept;

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
         */
        explicit Skeleton(const std::string& name);

        /**
         * @brief Constructor
         *
         * Protected constructor, as this class serves only as a
         * base for concrete test classes.
         * 
         * @param[in] name Name of the test as is displayed in logs
         * @param[in] logger A custom logger to be used for all outputs
         */
        Skeleton(const std::string& name, const cpplog::logger::Logger& logger);

        /**
         * @brief Constructor
         *
         * Protected constructor, as this class serves only as a
         * base for concrete test classes.
         *
         * @param[in] name Name of the test as is displayed in logs
         * @param[in] logger A custom logger to be used for all outputs
         */
        Skeleton(const std::string& name, cpplog::logger::Logger& logger);

        ///< The logger to be used for all outputs including test results.
        cpplog::logger::Logger& logger;

    private:
        std::string name; ///< Name of the test

        ///< internal Logger in case none is provided by client
        std::optional<cpplog::logger::Logger> internalLogger;

        bool exitOnFail = true; ///< Exit if test fails
        bool keepSandBox = false; ///< Skip clean up of the sandbox
        bool keepOldSandBox = false; ///< Skip clean up of previous sandbox
        ///< Skip entire clean up of sandbox and prevent test specific clean up call
        bool skipCleanUp = false; 

        std::filesystem::path cwd; ///< Stores current working directory to return to after test

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
         * @brief Setup a sandbox for a concrete test class
         * to be used
         */
        void setupSandBox(const std::string& directory);

        /**
         * @brief Clean up the previously created sand box
         */
        void cleanUpSandBox(const std::string& directory);

    };

}

#endif