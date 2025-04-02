#include <libcpptest/setup/Sandbox.hpp>

#include <libcpplog/logger/Logger.hpp>

#include <filesystem>
#include <stdexcept>
#include <string>

namespace cpptest::setup {

    Sandbox::Sandbox(
        std::string directoryPath,
        cpplog::logger::Logger& logger,
        bool keep,
        bool keepPrevious) :       
            directoryPath{ std::move(directoryPath) },
            logger{ logger },
            cwd{ std::filesystem::current_path() },
            keep{ keep },
            keepPrevious{ keepPrevious } {
        
        logger.log(
            "Creating integration test sandbox '"
            + std::filesystem::absolute(this->directoryPath).string() + "'.");
        if (!this->keepPrevious) {
            std::filesystem::remove_all(this->directoryPath);
        }
        if (!std::filesystem::exists(this->directoryPath)) {
            if (!std::filesystem::create_directory(this->directoryPath)) {
                throw std::runtime_error("Wasn't able to create directory '"
                    + this->directoryPath + "'.");
            }
        }
        std::filesystem::current_path(this->directoryPath);
    }

    Sandbox::~Sandbox() {
        std::filesystem::current_path(cwd);
        if (!keep) {
            logger.log("Cleaning up integration test sandbox directory '" + directoryPath + "'.");
            std::filesystem::remove_all(directoryPath);
        }
    }

}