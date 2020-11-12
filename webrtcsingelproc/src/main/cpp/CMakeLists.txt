cmake_minimum_required(VERSION 3.6)

include_directories(${CMAKE_CURRENT_LIST_DIR}/signalproc)
include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})
add_library(agcjni
        SHARED
        agc_jni.cpp
        )

add_library(wktimer
        STATIC
        IMPORTED)
set_target_properties(wktimer
        PROPERTIES
        IMPORTED_LOCATION     ${CMAKE_CURRENT_LIST_DIR}/libs/${ANDROID_ABI}/libwktimer.a)

add_library(oboeresampler
        STATIC
        IMPORTED)
set_target_properties(oboeresampler
        PROPERTIES
        IMPORTED_LOCATION     ${CMAKE_CURRENT_LIST_DIR}/libs/${ANDROID_ABI}/liboboeresampler.a)


add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/signalproc)



find_library(
        log-lib
        log)

target_link_libraries(
        agcjni
        oboeresampler
        signalproc
        wktimer
        ${log-lib})