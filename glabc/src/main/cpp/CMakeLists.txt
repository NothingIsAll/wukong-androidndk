cmake_minimum_required(VERSION 3.6)

include_directories(${CMAKE_CURRENT_LIST_DIR}/findcard1.3.8/findcard)

add_library(glabc
        SHARED
        ShapeObj/GLShaderToProgram.cpp
        MyGLRenderContext.cpp
        glabc_jni.cpp)

find_library(
        log-lib
        log)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/ShapeObj)
target_link_libraries(glabc
        shapeobj
        android
        GLESv2
        EGL
        z
        OpenSLES
        ${log-lib})