find_package(LIBCPPLOG
    NAMES
        cpplog
        libcpplog
    REQUIRED
)

set(LIBCPPTEST_INCLUDE_DIRS ${LIBCPPTEST_DIR}/include ${LIBCPPLOG_DIR}/include)
set(LIBCPPTEST_LIBRARY_DIR ${LIBCPPTEST_DIR}/lib ${LIBCPPLOG_DIR}/lib)
set(LIBCPPTEST_LIB_NAME libcpptest)

if (WIN32)
    string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_TO_UPPER)
    if (${CMAKE_BUILD_TYPE_TO_UPPER} STREQUAL "DEBUG")
        set(LIBCPPTEST_LIB_NAME libcpptestd)
    endif()  
endif()

set(LIBCPPTEST ${LIBCPPTEST_DIR}/lib/${LIBCPPTEST_LIB_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX})