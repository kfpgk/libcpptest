#include <libcpptest/integration_test/Fail.hpp>

#include <stdexcept>
#include <string>

namespace cpptest::integration_test {

    Fail::Fail(std::string message) :
        std::logic_error{ std::move(message) } {

    }

}