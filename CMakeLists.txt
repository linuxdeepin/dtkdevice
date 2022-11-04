# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

cmake_minimum_required(VERSION 3.13)

# If do't define version number, specify the version number
set(VERSION "1.0.0" CACHE STRING "define project version")

project(dtkdevice
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/linuxdeepin/dtkdevice
    DESCRIPTION "dtk library device"
    VERSION ${VERSION}
)


add_subdirectory(dtklsdevice)


