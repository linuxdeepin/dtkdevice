file(GLOB OUTER_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/../../src/3rdparty/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
)

file(GLOB OUTER_HEADER
    ${CMAKE_CURRENT_LIST_DIR}/../../src/3rdparty/*.h
    ${CMAKE_CURRENT_LIST_DIR}/../../include/dtkdevice/lsdevice/*.h
    ${CMAKE_CURRENT_LIST_DIR}/../../include/dtkdevice/global/*.h
)

set(LS_SRCS
  ${OUTER_HEADER}
  ${OUTER_SOURCE}
)
