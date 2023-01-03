set(LIB_NAME dtkdevice)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-DLIBDTKDEVICE_LIBRARY)

# find_package
find_package(PkgConfig REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS DBus)


pkg_search_module(LIB_NL3 REQUIRED libnl-3.0)
pkg_search_module(LIB_NL3_ROUTE REQUIRED libnl-route-3.0)

include_directories(${LIB_NL3_INCLUDE_DIRS})
include_directories(${LIB_NL3_ROUTE_INCLUDE_DIRS})
include(lsdevice/lsdevice.cmake)

add_library(${LIB_NAME} SHARED
    ${LS_SRCS}
)

target_link_libraries(
    ${LIB_NAME} PUBLIC
    Qt5::Core
    Qt5::DBus
    ${LIB_NL3_LIBRARIES}
    ${LIB_NL3_ROUTE_LIBRARIES}
)

target_include_directories(${LIB_NAME} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/3rdparty>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/global>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/lsdevice>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/DtkDevice>
)

set_target_properties(${LIB_NAME} PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
)

install(TARGETS ${LIB_NAME} DESTINATION ${LIBRARY_INSTALL_DIR})
install(DIRECTORY ../include/DDevice/ DESTINATION "${INCLUDE_INSTALL_DIR}" FILES_MATCHING PATTERN "*")
install(DIRECTORY ../include/lsdevice/ DESTINATION "${INCLUDE_INSTALL_DIR}" FILES_MATCHING PATTERN "*")
install(DIRECTORY ../include/global/ DESTINATION "${INCLUDE_INSTALL_DIR}" FILES_MATCHING PATTERN "*")
