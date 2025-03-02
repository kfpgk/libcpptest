#include <libcpptest/integration_test/MultiTestStub.test.hpp>
#include <libcpptest/integration_test/TestCase.hpp>
#include <libcpptest/exception/Exception.hpp>


namespace cpptest::integration_test::unit_test {

   MultiTestStub::MultiTestStub(bool testCase1Passes, bool testCase2Passes) noexcept :
        MultiTest("Multi test stub", { std::cout, { } }),
        testPasses{testCase1Passes, testCase2Passes} {

    }

    bool MultiTestStub::getSetupCalled() const noexcept {
        return setupCalled;
    }

    bool MultiTestStub::getPerformCalled(std::size_t testCaseNo) const noexcept {
        return performCalled.at(testCaseNo - 1);
    }

    bool MultiTestStub::getEvaluateCalled(std::size_t testCaseNo) const noexcept {
        return evaluateCalled.at(testCaseNo - 1);
    }

    bool MultiTestStub::getCleanUpCalled() const noexcept {
        return cleanUpCalled;
    }

    void MultiTestStub::addTestCases() {
        addTestCase({
            .name = "test case 1",
            .perform = std::bind(&MultiTestStub::performTestCase1, this),
            .evaluate = std::bind(&MultiTestStub::evaluateTestCase1, this)
            });

        addTestCase({
            .name = "test case 2",
            .perform = std::bind(&MultiTestStub::performTestCase2, this),
            .evaluate = std::bind(&MultiTestStub::evaluateTestCase2, this)
            });
    }

    void MultiTestStub::setup() {
        setupCalled = true;
    }

    void MultiTestStub::performTestCase1() {
        performCalled[0] = true;
    }

    void MultiTestStub::evaluateTestCase1() {
        evaluateCalled[0] = true;
        if (!testPasses[0]) {
            throw exception::Exception("Test case 1 failed.");
        }        
    }

    void MultiTestStub::performTestCase2() {
        performCalled[1] = true;
    }

    void MultiTestStub::evaluateTestCase2() {
        evaluateCalled[1] = true;
        if (!testPasses[1]) {
            throw exception::Exception("Test case 2 failed.");
        }          
    }

    void MultiTestStub::cleanUp() {
        cleanUpCalled = true;
    }

}