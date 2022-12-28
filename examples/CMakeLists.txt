# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

set(BIN_NAME demo-dtkdevice)

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
find_package(Qt5 REQUIRED COMPONENTS Gui)
find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS DBus)

file(GLOB_RECURSE INCLUDE_FILES
    "../include/dtkdevice/lsdevice/*.h"
    "../include/dtkdevice/global/*.h"
)
file(GLOB_RECURSE SRCS
    "./*.h"
    "./*.cpp"
)

include_directories(../include/dtkdevice/lsdevice)
include_directories(../include/dtkdevice/global)

add_executable(${BIN_NAME}
    ${INCLUDE_FILES}
    ${SRCS}
)

target_include_directories(${BIN_NAME} PUBLIC
    Qt5::Core
    Qt5:DBus
)

target_link_libraries(${BIN_NAME} PRIVATE
    Qt5::Core
    Qt5::DBus
    dtkdevice
)

install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${BIN_NAME})
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
