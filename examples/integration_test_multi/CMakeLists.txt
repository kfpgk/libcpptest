add_executable(integration_test_multi
    main.cpp
    FileReaderTest.cpp
    FileReader.cpp)

find_package(LIBCPPLOG
    NAMES
        cpplog
        libcpplog
    REQUIRED
)

find_package(LIBCPPTEST
    NAMES
        cpptest
        libcpptest
    REQUIRED
)

target_link_libraries(integration_test_multi
    PRIVATE
        ${LIBCPPLOG}
        ${LIBCPPTEST}
)

target_include_directories(integration_test_multi
    PRIVATE        
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_BINARY_DIR}
        "${LIBCPPLOG_INCLUDE_DIRS}"
        "${LIBCPPTEST_INCLUDE_DIRS}"
)