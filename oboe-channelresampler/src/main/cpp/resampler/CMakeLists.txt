cmake_minimum_required(VERSION 3.10)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})

file(GLOB resampler_SRC  ${CMAKE_CURRENT_LIST_DIR}/*.cpp )

add_library(oboeresampler
        STATIC
        ${resampler_SRC}
        )



find_library(
        log-lib
        log)


target_link_libraries(
        oboeresampler
        ${log-lib})