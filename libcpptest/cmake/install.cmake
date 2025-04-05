set(libcpptest_TARGETS libcpptest-targets)

set(PUBLIC_HEADERS
    integration_test/Fail.hpp
    integration_test/TestCase.hpp
    integration_test/MultiTest.hpp
    integration_test/SingleTest.hpp
    integration_test/Skeleton.hpp
)

install(TARGETS libcpptest 
    EXPORT ${libcpptest_TARGETS}
    RUNTIME DESTINATION "${libcpptest_INSTALL_BINDIR}"
    LIBRARY DESTINATION "${libcpptest_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${libcpptest_INSTALL_LIBDIR}"
    INCLUDES DESTINATION "${libcpptest_INSTALL_INCLUDEDIR}"
)

foreach(header_file ${PUBLIC_HEADERS})
    get_filename_component(header_dir ${header_file} DIRECTORY)
    install(
        FILES 
            ${header_file} 
        DESTINATION 
            "${libcpptest_INSTALL_INCLUDEDIR}/libcpptest/${header_dir}"
    )
endforeach()