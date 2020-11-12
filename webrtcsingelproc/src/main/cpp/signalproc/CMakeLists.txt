cmake_minimum_required(VERSION 3.10)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})

file(GLOB signalproc_SRC  ${CMAKE_CURRENT_LIST_DIR}/*.c )

add_library(signalproc
        STATIC
        ${signalproc_SRC}
        )



find_library(
        log-lib
        log)

target_link_libraries(
        signalproc
        ${log-lib})