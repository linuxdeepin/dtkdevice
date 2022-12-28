# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

set(BIN_NAME ut-dtkdevice)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# dbus
set(CMAKE_CXX_FLAGS "-fno-access-control -ldl")
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
add_definitions(-DPREFIX="${CMAKE_PREFIX_PATH}")
add_definitions(-DOS_VERSION_TEST_FILE="/tmp/etc/os-version")
find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS DBus)

#add_definitions(-DUSE_MOCK_INTERFACE)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-access-control -fno-inline -Wno-pmf-conversions")

file(GLOB_RECURSE INCLUDE_FILES
    "../include/dtkdevice/lsdevice/*.h"
    "../include/dtkdevice/global/*.h"
    "../src/3rdparty/*.h"
)
file(GLOB_RECURSE SRCS
    "../src/*.h"
    "../src/*.cpp"
    "../src/3rdparty/*.cpp"
    "../src/3rdparty/*.h"
)
file(GLOB_RECURSE TEST_FILES "./*.h" "./*.cpp")

include_directories(
    "../include/dtkdevice/lsdevice"
    "../include/dtkdevice/global"
    "../src/3rdparty"
    "../src/dbus"
)

add_executable(${BIN_NAME}
    ${INCLUDE_FILES}
    ${SRCS}
    ${TEST_FILES}
    ${DFAKE_INTERFACE_DBUS_XML}
)

target_include_directories(${BIN_NAME} PUBLIC
    Qt5::Core
    Qt5::DBus
    ${GLIB_INCLUDE_DIRS}
    ${GIOUNIX_INCLUDE_DIRS}
)

target_link_libraries(${BIN_NAME} PRIVATE
    Qt5::Core
    Qt5::DBus
    ${GLIB_LIBRARIES}
    ${GIOUNIX_LIBRARIES}
    -lpthread
    -lgcov
    -lgtest
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${BIN_NAME} PRIVATE -fprofile-instr-generate -ftest-coverage)
endif()
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${BIN_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
endif()

enable_testing()
add_test(NAME ${BIN_NAME} COMMAND ${BIN_NAME})
