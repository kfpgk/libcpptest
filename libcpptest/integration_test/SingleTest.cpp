#include <libcpptest/integration_test/SingleTest.hpp>

#include <libcpplog/logger/Logger.hpp>

namespace cpptest::integration_test {

    using namespace cpplog::logger;

    SingleTest::SingleTest(const std::string& name) :
        Skeleton{name} {

    }

    SingleTest::SingleTest(const std::string& name, const cpplog::logger::Logger& logger) :
        Skeleton{ name, logger } {

    }

    SingleTest::SingleTest(const std::string& name, cpplog::logger::Logger& logger) :
        Skeleton{ name, logger } {

    }

    void SingleTest::wrapPerform() {
        logger.log("--- perform ---");
        perform();
    }

    void SingleTest::wrapEvaluate() {
        logger.log("--- evaluate ---");
        evaluate();
    }

    void SingleTest::doRun() {
        wrapPerform();
        wrapEvaluate();
    }

}

