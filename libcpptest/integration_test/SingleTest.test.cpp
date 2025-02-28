#include <libcpptest/integration_test/SingleTest.test.hpp>
#include <libcpptest/integration_test/SingleTestStub.test.hpp>
#include <libcpplog/logger/Log.hpp>

#include <cassert>

int main(int argc, char* argv[]) {

    using namespace cpptest::integration_test::unit_test;
    SingleTestTest test;

    test.passingTest();
    test.failingTest();

    using namespace cpplog::logger;
    log(LogLevel::Result, "UT: integration_test::SingleTest passed.");
    return 0;
}

namespace cpptest::integration_test::unit_test {

    using namespace cpplog::logger;

    void SingleTestTest::passingTest() const {
        log(LogLevel::Info, "Running test");

        SingleTestStub test(true);

        bool result = test.run();

        assert(result);
        assert(test.getSetupCalled());
        assert(test.getPerformCalled());
        assert(test.getEvaluateCalled());
        assert(test.getCleanUpCalled());
    }

    void SingleTestTest::failingTest() const {
        log(LogLevel::Info, "Running test");

        SingleTestStub test(false);

        test.setExitOnFail(false);
        bool result = test.run();

        assert(!result);
        assert(test.getSetupCalled());
        assert(test.getPerformCalled());
        assert(test.getEvaluateCalled());
        assert(test.getCleanUpCalled());
    }

}
