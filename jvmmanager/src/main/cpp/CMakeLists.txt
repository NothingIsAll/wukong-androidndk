cmake_minimum_required(VERSION 3.6)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})
add_library(javacalljni
        SHARED
        com_example_jvmmanager_JavaThreadCallTest.cpp
        JniThreadCallJavaCallBack.cpp
        JniThreadTest.cpp
        )

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/jvmmanager)


find_library(
        log-lib
        log)

target_link_libraries(
        javacalljni
        jnienvmanager
        ${log-lib})