#ifndef LIBCPPTEST_EXCEPTION_EXCEPTION_HPP
#define LIBCPPTEST_EXCEPTION_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace cpptest::exception {

    /**
     * @brief `libcpptest` default exception
     * 
     * Catch this to catch all `libcpptest`
     * exceptions. 
     */
    class Exception : public std::runtime_error {

    public:
        /**
         * @brief Constructor
         */
        explicit Exception(const std::string& errorMessage);

    };

}

#endif