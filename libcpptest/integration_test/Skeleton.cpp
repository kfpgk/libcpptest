#include <libcpptest/integration_test/Skeleton.hpp>
#include <libcpptest/exception/Exception.hpp>
#include <libcpptest/config/config.h>

#include <libcpplog/logger/Log.hpp>

#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <exception>

namespace cpptest::integration_test {

    using namespace cpplog::logger;
    using namespace exception;

    Skeleton::Skeleton(const std::string& name) :
        name{name},
        internalLogger{ std::in_place, std::cout, LogFormat::defaultValue() },
        logger{ *internalLogger },
        cwd{std::filesystem::current_path()} {

    }

    Skeleton::Skeleton(const std::string& name, const Logger& logger) :
        name{ name },
        internalLogger{ logger },
        logger{ *internalLogger },
        cwd{ std::filesystem::current_path() } {

    }

    Skeleton::Skeleton(const std::string& name, Logger& logger) :
        name{ name },
        internalLogger { std::nullopt },
        logger{ logger },
        cwd{ std::filesystem::current_path() } {

    }

    bool Skeleton::run() {
        logger.log("Running integration test: '" + name + "'");

        try {
            wrapSetup();
            doRun();
            wrapCleanUp();
        } catch (const std::exception& e) {
            logger.log(LogLevel::Error, e.what());
            logger.log(LogLevel::Result, "Integration test '" + name + "' failed.");
            wrapCleanUp();
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

    void Skeleton::setKeepOldSandBox(bool value) noexcept {
        this->keepOldSandBox = value;
    }

    void Skeleton::setSkipCleanUp(bool value) noexcept {
        this->skipCleanUp = value;
    }

    void Skeleton::wrapSetup() {
        logger.log("--- setup ---");
        setupSandBox(config::integration_sandbox_dir);
        setup();
    }

    void Skeleton::wrapCleanUp() {
        if (!cleanUpCalled) {
            cleanUpCalled = true;
            logger.log("--- clean up ---");
            if (skipCleanUp) {
                logger.log("Skip clean up");
                std::filesystem::current_path(cwd);
            } else {
                cleanUp();
                std::filesystem::current_path(cwd);
                if (!keepSandBox) {
                    cleanUpSandBox(config::integration_sandbox_dir);
                }
            }
        }
    }

    void Skeleton::setupSandBox(const std::string& directory) {
        logger.log(
            "Creating integration test sandbox '" 
            + std::filesystem::absolute(directory).string() + "'.");
        this->cwd = std::filesystem::current_path();
        if (!keepOldSandBox) {
            std::filesystem::remove_all(directory);
        }
        if (!std::filesystem::exists(directory)) {
            if (!std::filesystem::create_directory(directory)) {
                throw Exception("Wasn't able to create directory '"
                    + directory + "'.");
            }
        }     
        std::filesystem::current_path(directory);
    }

    void Skeleton::cleanUpSandBox(const std::string& directory) {
        logger.log("Cleaning up integration test sandbox directory '" + directory + "'.");
        std::filesystem::remove_all(directory);
    }

    void Skeleton::setup() {
        logger.log("Custom setup() not implemented");
    }

    void Skeleton::cleanUp() {
        logger.log("Custom cleanUp() not implemented");
    }

}