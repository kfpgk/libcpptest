cmake_minimum_required(VERSION 3.20)

project(libcpptest-examples VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Use double quotes to account for case when CMAKE_BUILD_TYPE is empty.
string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    add_compile_definitions(DEBUG_BUILD=1)
endif()

add_subdirectory(integration_test_multi)
add_subdirectory(integration_test_single)