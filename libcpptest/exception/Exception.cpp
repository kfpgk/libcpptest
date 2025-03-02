#include <libcpptest/exception/Exception.hpp>

#include <stdexcept>
#include <string>

namespace cpptest::exception {

    Exception::Exception(const std::string& errorMessage) :
        std::runtime_error{errorMessage} {

    }

}