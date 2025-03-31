include(GNUInstallDirs)

if(NOT DEFINED libcpptest_INSTALL_INCLUDEDIR)
  set(libcpptest_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}")
endif()

if(NOT DEFINED libcpptest_INSTALL_BINDIR)
  set(libcpptest_INSTALL_BINDIR "${CMAKE_INSTALL_BINDIR}")
endif()

if(NOT DEFINED libcpptest_INSTALL_LIBDIR)
  set(libcpptest_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}")
endif()

if(NOT DEFINED libcpptest_INSTALL_CONFIGDIR)
  set(libcpptest_INSTALL_CONFIGDIR "${CMAKE_INSTALL_PREFIX}/cmake")
endif()