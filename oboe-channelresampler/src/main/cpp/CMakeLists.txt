cmake_minimum_required(VERSION 3.6)

include_directories(${CMAKE_CURRENT_LIST_DIR}/resampler)
include_directories(${CMAKE_CURRENT_LIST_DIR}/libs)
include_directories(${CMAKE_CURRENT_LIST_DIR})
add_library(resamplerjni
        SHARED
        com_example_oboe_channelresampler_ResamplerTest.cpp
        )

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/resampler)

add_library(wktimer
        STATIC
        IMPORTED)
set_target_properties(wktimer
        PROPERTIES
        IMPORTED_LOCATION     ${CMAKE_CURRENT_LIST_DIR}/libs/${ANDROID_ABI}/libwktimer.a)

find_library(
        log-lib
        log)

target_link_libraries(
        resamplerjni
        oboeresampler
        wktimer
        ${log-lib})