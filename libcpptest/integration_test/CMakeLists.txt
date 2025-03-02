target_sources(libcpptest
    PRIVATE
        MultiTest.cpp
        SingleTest.cpp
        Skeleton.cpp
)

if(BUILD_UNIT_TESTS)
    enable_testing()

    add_executable(SingleTest_test
        SingleTest.test.cpp
        SingleTestStub.test.cpp
    )
    target_include_directories(SingleTest_test 
        PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${CMAKE_BINARY_DIR}
            "${LIBCPPLOG_INCLUDE_DIRS}"
    )
    target_link_libraries(SingleTest_test
        PRIVATE
            libcpptest
            ${LIBCPPLOG}
    )
    add_test(
        NAME "UT integration_test::SingleTest"
        COMMAND SingleTest_test
    )

    add_executable(MultiTest_test
        MultiTest.test.cpp
        MultiTestStub.test.cpp
    )
    target_include_directories(MultiTest_test 
        PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${CMAKE_BINARY_DIR}
            "${LIBCPPLOG_INCLUDE_DIRS}"
    )
    target_link_libraries(MultiTest_test
        PRIVATE
            libcpptest
            ${LIBCPPLOG}
    )
    add_test(
        NAME "UT integration_test::MultiTest"
        COMMAND MultiTest_test
    )
endif()