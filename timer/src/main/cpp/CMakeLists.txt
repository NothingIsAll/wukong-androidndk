cmake_minimum_required(VERSION 3.6)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})
add_library(flltimer
        SHARED
        com_example_timer_TimerBlock.cpp
        )

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/timer)


find_library(
        log-lib
        log)

target_link_libraries(
        flltimer
        wktimer
        ${log-lib})