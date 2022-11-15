# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

set(LIB ${BIN_NAME})

set(MONITOR monitor)
add_executable(${MONITOR} devicemonitor.cpp)
target_include_directories(${MONITOR} PUBLIC
    "../include"
    )
target_link_libraries(${MONITOR} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    ${LIB}
    )
