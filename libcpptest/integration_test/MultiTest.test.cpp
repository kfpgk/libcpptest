#include <libcpptest/integration_test/MultiTest.test.hpp>
#include <libcpptest/integration_test/MultiTestStub.test.hpp>

#include <libcpplog/logger/Log.hpp>

#include <cassert>

int main(int argc, char* argv[]) {

    using namespace cpptest::integration_test::unit_test;
    MultiTestTest test;

    test.noTestCasesAdded();
    test.allPass();
    test.firstFails();
    test.secondFails();

    using namespace cpplog::logger;
    log(LogLevel::Result, "UT: integration_test::MultiTest passed.");
    return 0;
}

namespace cpptest::integration_test::unit_test {

    using namespace cpplog::logger;

    void MultiTestTest::noTestCasesAdded() const {
        log(LogLevel::Info, "Running noTestCasesAdded()");

        MultiTestStub test(true, true);

        bool result = test.run();

        assert(result);
        assert(test.getSetupCalled());
        assert(!test.getPerformCalled(1));
        assert(!test.getPerformCalled(2));
        assert(!test.getEvaluateCalled(1));
        assert(!test.getEvaluateCalled(2));
        assert(test.getCleanUpCalled());
    }

    void MultiTestTest::allPass() const {
        log(LogLevel::Info, "Running test");

        MultiTestStub test(true, true);
        test.addTestCases();
        test.setExitOnFail(false);

        bool result = test.run();

        assert(result);
        assert(test.getSetupCalled());
        assert(test.getPerformCalled(1));
        assert(test.getPerformCalled(2));
        assert(test.getEvaluateCalled(1));
        assert(test.getEvaluateCalled(2));
        assert(test.getCleanUpCalled());
    }

    void MultiTestTest::firstFails() const {
        log(LogLevel::Info, "Running test");

        MultiTestStub test(false, true);
        test.addTestCases();
        test.setExitOnFail(false);

        bool result = test.run();

        assert(!result);
        assert(test.getSetupCalled());
        assert(test.getPerformCalled(1));
        assert(!test.getPerformCalled(2));
        assert(test.getEvaluateCalled(1));
        assert(!test.getEvaluateCalled(2));
        assert(test.getCleanUpCalled());
    }

    void MultiTestTest::secondFails() const {
        log(LogLevel::Info, "Running test");

        MultiTestStub test(true, false);
        test.addTestCases();
        test.setExitOnFail(false);

        bool result = test.run();

        assert(!result);
        assert(test.getSetupCalled());
        assert(test.getPerformCalled(1));
        assert(test.getPerformCalled(2));
        assert(test.getEvaluateCalled(1));
        assert(test.getEvaluateCalled(2));
        assert(test.getCleanUpCalled());
    }

}
