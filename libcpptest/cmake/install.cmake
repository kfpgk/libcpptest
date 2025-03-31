set(libcpptest_TARGETS libcpptest-targets)

set(PUBLIC_HEADERS
    exception/Exception.hpp
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

foreach(header ${PUBLIC_HEADERS})
    get_filename_component(header_dir ${header} DIRECTORY)
    install(
        FILES 
            ${file} 
        DESTINATION 
            "${libcpptest_INSTALL_INCLUDEDIR}/libcpptest/${header_dir}"
        COMPONENT
            Devel)
endforeach()