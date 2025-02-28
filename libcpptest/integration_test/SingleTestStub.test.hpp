#ifndef LIBCPPTEST_INTEGRATION_TEST_SINGLE_TEST_STUB_TEST_HPP
#define LIBCPPTEST_INTEGRATION_TEST_SINGLE_TEST_STUB_TEST_HPP

#include <libcpptest/integration_test/SingleTest.hpp>

namespace cpptest::integration_test::unit_test {

    /**
     * @brief Stub class for SingleTest class
     * 
     * This class provides overrides for the
     * test template methods.
     */
    class SingleTestStub : public SingleTest {

    public:
        /**
         * @brief Constructor
         * 
         * @param[in] testPasses Defines whether evaluation shall pass (true) or fail (false)
         */
        explicit SingleTestStub(bool testPasses) noexcept;

        /**
         * @brief Returns whether `setup()` has been called at least once.
         */
        bool getSetupCalled() const noexcept;

        /**
         * @brief Returns whether `perform()` has been called at least once.
         */
        bool getPerformCalled() const noexcept;

        /**
         * @brief Returns whether `evaluate()` has been called at least once.
         */
        bool getEvaluateCalled() const noexcept;

        /**
         * @brief Returns whether `cleanUp()` has been called at least once.
         */
        bool getCleanUpCalled() const noexcept;

    private:
        bool setupCalled = false; ///< Flag that indicates `setup()` has been called
        bool performCalled = false; ///< Flag that indicates `perform()` has been called
        bool evaluateCalled = false; ///< Flag that indicates `evaluate()` has been called
        bool cleanUpCalled = false; ///< Flag that indicates `cleanUp()` has been called

        bool testPasses; ///< Specifies if `evaluate()` shall pass or fail

        /**
         * @brief Stub for `setup()`
         */
        void setup() override;

        /**
         * @brief Stub for `perform()`
         */
        void perform() override;

        /**
         * @brief Stub for `evaluate()`
         */
        void evaluate() override;

        /**
         * @brief Stub for `cleanUp()`
         */
        void cleanUp() override;

    };

}

#endif