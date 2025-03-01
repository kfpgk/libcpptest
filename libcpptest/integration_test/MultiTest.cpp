#include <libcpptest/integration_test/MultiTest.hpp>
#include <libcpptest/integration_test/TestCase.hpp>

#include <libcpplog/logger/Logger.hpp>

#include <string>

namespace cpptest::integration_test {

    using namespace cpplog::logger;

    MultiTest::MultiTest(const std::string& name) :
        Skeleton{name} {

    }

    MultiTest::MultiTest(const std::string& name, const cpplog::logger::Logger& logger) :
        Skeleton{ name, logger } {

    }

    MultiTest::MultiTest(const std::string& name, cpplog::logger::Logger& logger) :
        Skeleton{ name, logger } {

    }

    void MultiTest::wrapPerform(const TestCase& testCase) {
        logger.log("--- perform test case '" + testCase.name + "' ---");
        testCase.perform();
    }

    void MultiTest::wrapEvaluate(const TestCase& testCase) {
        logger.log("--- evaluate test case '" + testCase.name + "' ---");
        testCase.evaluate();
    }

    void MultiTest::addTestCase(TestCase testCase) {
        testCases.push_back(testCase);
    }

    void MultiTest::doRun() {
        int noOfTestCases = testCases.size();
        if (noOfTestCases == 0) {
            logger.log(LogLevel::Warning, 
                "This test contains no test cases. Add test cases with `addTestCase()`.");
        } else {
            logger.log("Running " + std::to_string(noOfTestCases) + " testcase(s).");
            int count = 1;
            for (auto&& it = testCases.begin(); it != testCases.end(); it++, count++) {
                logger << LogStream()
                       << "--- Running testcase " 
                       << count << "/" << noOfTestCases 
                       << " ---" << std::endl;
                wrapPerform(*it);
                wrapEvaluate(*it);
                logger.log("Testcase '" + it->name + "' passed.");
            }
        }
    }

}

