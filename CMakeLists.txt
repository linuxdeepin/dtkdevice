cmake_minimum_required(VERSION 3.10)

# If do't define version number, specify the version number
set(DVERSION "1.0.0" CACHE STRING "define project version")

project(dtkdevice
    VERSION ${DVERSION}
    DESCRIPTION "DTK library for device."
    HOMEPAGE_URL https://github.com/linuxdeepin/dtkdevice
    LANGUAGES CXX C
)
message(STATUS ${PROJECT_VERSION})

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()
set (INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/libdtk-${CMAKE_PROJECT_VERSION}/DDevice")
set (LIBRARY_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
set (MKSPECS_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/qt5/mkspecs/modules" CACHE STRING "INSTALL DIR FOR qt pri files")
set (CONFIG_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/DtkCore" CACHE STRING "Install dir for cmake config files")

set (BUILD_EXAMPLES ON CACHE BOOL "Build examples")

if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()
set (BUILD_DOCS ON CACHE BOOL "Generate doxygen-based documentation")

# CXX FILAGS
set(CMAKE_CXX_STANDARD 11)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--as-needed")
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_TESTING ON)
  endif ()
  string(REPLACE "-O3" "-Ofast" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
endif()

if (BUILD_DOCS)
  add_subdirectory(docs)
endif ()

add_subdirectory(src)

if(BUILD_TESTING)
  message("==================================")
  message("       Now Testing is enabled     ")
  message("==================================")
  enable_testing()
  add_subdirectory(tests)
endif()
if(BUILD_EXAMPLES)
  message("===================================")
  message("You can build and run examples now ")
  message("===================================")
  add_subdirectory(examples)
endif()

configure_package_config_file(misc/DtkDeviceConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/DtkDeviceConfig.cmake
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/DtkDevice"
    PATH_VARS INCLUDE_INSTALL_DIR LIBRARY_INSTALL_DIR
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/DtkDeviceConfigVersion.cmake"
    VERSION ${DVERSION}
    COMPATIBILITY SameMajorVersion
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/DtkDeviceConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/DtkDeviceConfigVersion.cmake
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/DtkDevice"
)

configure_file(misc/dtkdevice.pc.in dtkdevice.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/dtkdevice.pc DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")

configure_file(misc/qt_lib_dtkdevice.pri.in qt_lib_dtkdevice.pri @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qt_lib_dtkdevice.pri DESTINATION "${MKSPECS_INSTALL_DIR}")
