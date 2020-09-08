cmake_minimum_required(VERSION 3.6)

add_library(micdecode
        STATIC
        tlmicdes.cpp
        )

add_library(micdecodejni
        SHARED
        com_example_micserialnumdes_MicnumDecode.cpp)


find_library(
        log-lib
        log)


target_link_libraries(
        micdecodejni
        micdecode
        ${log-lib})