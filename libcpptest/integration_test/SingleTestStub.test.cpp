#include <libcpptest/integration_test/SingleTestStub.test.hpp>
#include <libcpptest/exception/Exception.hpp>

namespace cpptest::integration_test::unit_test {

   SingleTestStub::SingleTestStub(bool testPasses) noexcept :
       SingleTest("Single test case stub", { std::cout, { } }),
        testPasses{testPasses} {

    }

    bool SingleTestStub::getSetupCalled() const noexcept {
        return setupCalled;
    }

    bool SingleTestStub::getPerformCalled() const noexcept {
        return performCalled;
    }

    bool SingleTestStub::getEvaluateCalled() const noexcept {
        return evaluateCalled;
    }

    bool SingleTestStub::getCleanUpCalled() const noexcept {
        return cleanUpCalled;
    }

    void SingleTestStub::setup() {
        setupCalled = true;
    }

    void SingleTestStub::perform() {
        performCalled = true;
    }

    void SingleTestStub::evaluate() {
        evaluateCalled = true;
        if (!testPasses) {
            throw exception::Exception("Test failed.");
        }
    }

    void SingleTestStub::cleanUp() {
        cleanUpCalled = true;
    }

}