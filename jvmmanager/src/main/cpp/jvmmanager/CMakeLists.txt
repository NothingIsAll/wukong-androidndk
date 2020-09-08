cmake_minimum_required(VERSION 3.6)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})
add_library(jnienvmanager
        SHARED
        JniThreadEnvManager.cpp
        JvmOBJ.cpp
        )



find_library(
        log-lib
        log)

target_link_libraries(
        jnienvmanager
        ${log-lib})