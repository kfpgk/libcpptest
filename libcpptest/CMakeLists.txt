add_library(libcpptest)

set_target_properties(libcpptest 
    PROPERTIES 
        PREFIX ""
)

if (WIN32)
    set_target_properties(libcpptest 
        PROPERTIES 
            DEBUG_POSTFIX "d"
    )
endif()

install(TARGETS libcpptest
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

set(PUBLIC_INCLUDE_PREFIX include/libcpptest)
install(FILES exception/Exception.hpp DESTINATION ${PUBLIC_INCLUDE_PREFIX}/exception)
install(FILES integration_test/TestCase.hpp DESTINATION ${PUBLIC_INCLUDE_PREFIX}/integration_test)
install(FILES integration_test/MultiTest.hpp DESTINATION ${PUBLIC_INCLUDE_PREFIX}/integration_test)
install(FILES integration_test/SingleTest.hpp DESTINATION ${PUBLIC_INCLUDE_PREFIX}/integration_test)

find_package(LIBCPPLOG
    NAMES
        cpplog
        libcpplog
    REQUIRED
)

target_link_libraries(libcpptest
    PRIVATE
        ${LIBCPPLOG}
)

target_include_directories(libcpptest
    PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_BINARY_DIR}
        "${LIBCPPLOG_INCLUDE_DIRS}"
)

target_sources(libcpptest
    PRIVATE
        "${LIBCPPLOG_INCLUDE_DIRS}/libcpplog/logger/Log.hpp"
)

if(BUILD_UNIT_TESTS)
    enable_testing()
endif()

add_subdirectory(exception)
add_subdirectory(integration_test)