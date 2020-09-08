cmake_minimum_required(VERSION 3.6)

include_directories(${CMAKE_CURRENT_LIST_DIR}/findcard1.3.8/findcard)
add_library(sofindcard
        SHARED
        SoFindCard.cpp
        com_example_findcard_FindcardTest.cpp
        Threads.cpp)


#
#include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
#add_library(sysresampler SHARED IMPORTED)
#set_target_properties(sysresampler PROPERTIES IMPORTED_LOCATION
#${CMAKE_CURRENT_LIST_DIR}/jnilibs/${ANDROID_ABI}/libspeexresampler.so)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} clang++ -std=c++11 -stdlib=libc++")
ADD_DEFINITIONS(-DVERSION="findcard-version-netcontrol-v1.3.8")
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/findcard1.3.8/tlcurllibmake/)
#add_library(findcard_static
#        STATIC
#        IMPORTED)
#set_target_properties(findcard_static
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_CURRENT_LIST_DIR}/solibs/libfindcard_static.a)

find_library(
        log-lib
        log)

target_link_libraries(
        sofindcard
        findcardhid_static
        ${log-lib})

