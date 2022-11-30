# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

# set(BIN_NAME ${CMAKE_PROJECT_NAME})

INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/src) 
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdparty)  
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/dtklsdevice/include)  
include_directories(../include)

file(GLOB_RECURSE INCLUDE_FILES "../include/*.h")
file(GLOB_RECURSE SRCS
    "./*.h"
    "./*.cpp"
    "../3rdparty/*.cpp"
    "../3rdparty/*.h"
)

message("lib name = ${BIN_NAME}")
add_library(${BIN_NAME} SHARED
    ${INCLUDE_FILES}
    ${SRCS}
)

set_target_properties(${BIN_NAME} PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

target_compile_definitions(${BIN_NAME} PRIVATE VERSION="${CMAKE_PROJECT_VERSION}")

find_package(PkgConfig REQUIRED)

target_include_directories(${BIN_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    # Qt${QT_VERSION_MAJOR}::DBus
)

target_link_libraries(${BIN_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    # Qt${QT_VERSION_MAJOR}::DBus
    # ${link3rd_LIBS}
)

install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${BIN_NAME})
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
