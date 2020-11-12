cmake_minimum_required(VERSION 3.6)

include_directories(${CMAKE_CURRENT_LIST_DIR}/findcard1.3.8/findcard)

add_library(glabc
        SHARED
        GLShaderToProgram.cpp
        glabc_jni.cpp)

find_library(
        log-lib
        log)

target_link_libraries(
        glabc
        android
        GLESv2
        EGL
        z
        OpenSLES
        ${log-lib})