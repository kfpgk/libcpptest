add_executable(integration_test_single
    main.cpp
    FileReader.cpp 
    TestReadLineFromFile.cpp)

find_package(LIBCPPTEST
    NAMES
        cpptest
        libcpptest
    REQUIRED
)

target_link_libraries(integration_test_single
    PRIVATE
        ${LIBCPPLOG}
        ${LIBCPPTEST}
)

target_include_directories(integration_test_single
    PRIVATE
        ${CMAKE_SOURCE_DIR}
        "${LIBCPPTEST_INCLUDE_DIRS}"
)