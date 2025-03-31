# Get access to helper functions for generating config files
include(CMakePackageConfigHelpers)

# Generate config file inside build tree
configure_package_config_file(
    cmake/config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/${libcpptest_config_file}"
    INSTALL_DESTINATION "${CMAKE_INSTALL_PREFIX}/libcpptest"
)

# Install config file to install tree
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/${libcpptest_config_file}"
  DESTINATION
    .
  COMPONENT
    Devel
)