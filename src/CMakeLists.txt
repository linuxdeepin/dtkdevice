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
find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS DBus)

include(lsdevice/lsdevice.cmake)

add_library(${LIB_NAME} SHARED
    ${LS_SRCS}
)

target_link_libraries(
    ${LIB_NAME} PUBLIC
    Qt5::Core
    Qt5::DBus
)

target_include_directories(${LIB_NAME} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/3rdparty>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/dtkdevice/global>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/dtkdevice/lsdevice>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/dtkdevice/DtkDevice>
)

set_target_properties(${LIB_NAME} PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
)

install(TARGETS ${LIB_NAME} DESTINATION ${LIBRARY_INSTALL_DIR})
install(DIRECTORY ../include/dtkdevice/DDevice/ DESTINATION "${INCLUDE_INSTALL_DIR}" FILES_MATCHING PATTERN "*")
install(DIRECTORY ../include/dtkdevice/lsdevice/ DESTINATION "${INCLUDE_INSTALL_DIR}" FILES_MATCHING PATTERN "*")
install(DIRECTORY ../include/dtkdevice/global/ DESTINATION "${INCLUDE_INSTALL_DIR}" FILES_MATCHING PATTERN "*")
