cmake_minimum_required(VERSION 3.6)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
add_library(md5checktest
        SHARED
        com_example_hash_md5_MD5Check.cpp
        )

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/hashlibpp)


find_library(
        log-lib
        log)

target_link_libraries(
        md5checktest
        hashcheck
        ${log-lib})

