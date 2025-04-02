# Set path to subdirectory holding cmake scripts
set(libcpptest_cmake_code_dir "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include("${libcpptest_cmake_code_dir}/set-install-dirs.cmake")

add_library(libcpptest)

# We want to install both release and debug build on Windows
# Use postfix for unique file names
if (WIN32)
    set_target_properties(libcpptest 
        PROPERTIES 
            DEBUG_POSTFIX "d"
    )
endif()

find_package(libcpplog
    NAMES
        cpplog
        libcpplog
    REQUIRED
)

get_target_property(libcpplog_INCLUDE_DIR CPPLOG::libcpplog INTERFACE_INCLUDE_DIRECTORIES)

target_link_libraries(libcpptest
    PUBLIC
        CPPLOG::libcpplog
)

target_include_directories(libcpptest
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${libcpptest_INSTALL_INCLUDEDIR}>
        "${libcpplog_INCLUDE_DIR}"
)

include("${libcpptest_cmake_code_dir}/install.cmake")

include("${libcpptest_cmake_code_dir}/create-package.cmake")

if(BUILD_UNIT_TESTS)
    enable_testing()
endif()

add_subdirectory(integration_test)
add_subdirectory(setup)