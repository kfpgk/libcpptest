add_executable(integration_test_multi
    main.cpp
    FileReader.cpp
    FileReaderTest.cpp)

find_package(LIBCPPTEST
    NAMES
        cpptest
        libcpptest
    REQUIRED
)

target_link_libraries(integration_test_multi
    PRIVATE
        ${LIBCPPTEST}
        ${LIBCPPLOG}
)

target_include_directories(integration_test_multi
    PRIVATE        
        ${CMAKE_SOURCE_DIR}
        "${LIBCPPTEST_INCLUDE_DIRS}"
)