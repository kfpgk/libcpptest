# Create targets file inside build tree
export(EXPORT ${libcpptest_TARGETS}
    FILE
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/${libcpptest_targets_file}"
    NAMESPACE 
        CPPTEST::
)

# Install the the targets file to the install tree
install(EXPORT ${libcpptest_TARGETS}
    FILE
        ${libcpptest_targets_file}
    DESTINATION 
        cmake
    NAMESPACE 
        CPPTEST::
)