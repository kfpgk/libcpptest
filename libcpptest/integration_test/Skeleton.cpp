#include <libcpptest/integration_test/Skeleton.hpp>
#include <libcpptest/integration_test/Fail.hpp>
#include <libcpptest/setup/Sandbox.hpp>
#include <libcpptest/config/config.hpp>

#include <libcpplog/logger/Log.hpp>
#include <libcpplog/debug/Debug.hpp>

#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <exception>

namespace cpptest::integration_test {

    using namespace cpplog::logger;

    Skeleton::Skeleton(std::string name, Logger& logger) :
        name{ std::move(name) },
        internalLogger{ std::nullopt },
        logger{ logger } {

    }

    Skeleton::Skeleton(std::string name, const Logger& logger) :
        name{ std::move(name) },
        internalLogger{ logger },
        logger{ *internalLogger } {

    }

    bool Skeleton::run() {
        logger.log("Running integration test: '" + name + "'");

        bool failed = false;

        try {
            setup::Sandbox sandbox(
                config::integration_sandbox_dir,
                logger, 
                keepSandBox,
                keepPreviousSandBox);

            { 
                Setup setup(*this); /* Setup */
                doRun();
            } /* Clean up */
            
        } catch (const Fail& e) {
            logger.log(LogLevel::Info, "Fail detected");
            logger.log(LogLevel::Error, e.what());
            failed = true;
        } catch (const std::exception& e) {
            logger.log(LogLevel::Info, "std::exception detected. Set test result to failed.");
            logger.log(LogLevel::Error, e.what());
            failed = true;
        } catch (...) {
            logger.log(LogLevel::Error, "Unknown exception occured during test run");
            failed = true;
        }

        if (failed) {
            logger.log(LogLevel::Result, "Integration test '" + name + "' failed.");
            if (exitOnFail) {
                exit(-1);
            }
            return false;
        }

        logger.log("--- test finished ---");
        logger.log(LogLevel::Result, "Integration test '" + name + "' passed.");
        return true;
    }

    void Skeleton::setExitOnFail(bool value) noexcept {
        this->exitOnFail = value;
    }

    void Skeleton::setKeepSandBox(bool value) noexcept {
        this->keepSandBox = value;
    }

    void Skeleton::setKeepPreviousSandBox(bool value) noexcept {
        this->keepPreviousSandBox = value;
    }

    void Skeleton::setSkipCleanUp(bool value) noexcept {
        this->skipCleanUp = value;
    }

    void Skeleton::wrapSetup() {
        logger.log("--- setup ---");
        setup();
    }

    void Skeleton::wrapCleanUp() {
        if (skipCleanUp) {
            logger.log("Skip clean up");
        } else {
            logger.log("--- clean up ---");
            cleanUp();
        }
    }

    void Skeleton::setup() {
        logger.log("Custom setup() not implemented");
    }

    void Skeleton::cleanUp() {
        logger.log("Custom cleanUp() not implemented");
    }

    Skeleton::Setup::Setup(Skeleton& skeleton) :
        skeleton{ skeleton } {

        this->skeleton.wrapSetup();
    }

    Skeleton::Setup::~Setup() {
        skeleton.wrapCleanUp();
    }

}