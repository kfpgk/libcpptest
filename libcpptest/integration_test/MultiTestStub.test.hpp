#ifndef LIBCPPTEST_INTEGRATION_TEST_MULTI_TEST_STUB_TEST_HPP
#define LIBCPPTEST_INTEGRATION_TEST_MULTI_TEST_STUB_TEST_HPP

#include <libcpptest/integration_test/MultiTest.hpp>

#include <array>
#include <cstddef>

namespace cpptest::integration_test::unit_test {

    /**
     * @brief Stub class for MultiTest class
     *
     * This class provides overrides for the
     * test template methods for two test
     * cases.
     */
    class MultiTestStub : public MultiTest {

    public:
        /**
         * @brief Constructor
         *
         * @param[in] testCase1Passes Defines whether evaluation of the first
         * test case shall pass (true) or fail (false)
         * @param[in] testCase2Passes Defines whether evaluation of the second
         * test case shall pass (true) or fail (false)
         */
        MultiTestStub(bool testCase1Passes, bool testCase2Passes) noexcept;

        /**
         * @brief Returns whether `setup()` has been called at least once.
         */
        bool getSetupCalled() const noexcept;

        /**
         * @brief Returns whether `perform()` for test case \p
         * has been called at least once.
         * 
         * @param[in] testCaseNo Index of test case for which to 
         * return the result starting at index '1'
         */
        bool getPerformCalled(std::size_t testCaseNo) const noexcept;

        /**
         * @brief Returns whether `evaluate()` for test case \p
         * has been called at least once.
         *
         * @param[in] testCaseNo Index of test case for which to
         * return the result starting at index '1'
         */
        bool getEvaluateCalled(std::size_t testCaseNo) const noexcept;

        /**
         * @brief Returns whether `cleanUpt()` has been called at least once.
         */
        bool getCleanUpCalled() const noexcept;

        /**
         * @brief Add the preconfigured test cases to the test.
         * 
         * Usually adding test cases is done inside the test class' constructor.
         * We separate this, so we can also create a unit test scenario with
         * no added test cases.
         */
        void addTestCases();

    private:
        static constexpr std::size_t numOfTestCases = 2; ///< Number of test cases
        ///< Array holding expected results of each test case
        std::array<bool, numOfTestCases> testPasses = {true};
        ///< Array holding indications for `perform()` called for each test case
        std::array<bool, numOfTestCases> performCalled = {false};
        ///< Array holding indications for `evaluate()` called for each test case
        std::array<bool, numOfTestCases> evaluateCalled = {false};
        bool setupCalled = false; ///< Flag that indicates `setup()` has been called
        bool cleanUpCalled = false; ///< Flag that indicates `cleanUp()` has been called

        /**
         * @brief Stub for `setup()`
         */
        void setup() override;

        /**
         * @brief Stub for `perform()` of test case 1
         */
        void performTestCase1();

        /**
         * @brief Stub for `evaluate()` of test case 1
         */
        void evaluateTestCase1();

        /**
         * @brief Stub for `perform()` of test case 2
         */
        void performTestCase2();

        /**
         * @brief Stub for `evaluate()` of test case 2
         */
        void evaluateTestCase2();

        /**
         * @brief Stub for `cleanUp()`
         */
        void cleanUp() override;
    };

}

#endif