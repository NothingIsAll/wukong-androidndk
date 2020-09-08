include_directories(${CMAKE_CURRENT_LIST_DIR}/../tlcurl/curl/)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../tljson/)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../tlpfinfo/)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../tlurlrule/)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../factory/)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../findcard/)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../indentyvertion/)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../globalenv/)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../decry/base64/)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../decry/serinumdes/)
include_directories(${CMAKE_CURRENT_LIST_DIR}/)


find_library(log-lib log)

add_library(findcardhid_static
        STATIC
  ${CMAKE_CURRENT_LIST_DIR}/../findcard/findcard.cpp
${CMAKE_CURRENT_LIST_DIR}/../factory/Mcreater.cpp
  ${CMAKE_CURRENT_LIST_DIR}/../indentyvertion/indentyvertion.cpp
        ${CMAKE_CURRENT_LIST_DIR}/../decry/serinumdes/des.cpp
  ${CMAKE_CURRENT_LIST_DIR}/../decry/serinumdes/descheck.cpp
        tlmicdes.cpp
        FindCardHid.cpp
        )


target_link_libraries(
        findcardhid_static
        ${log-lib}
        )
message(WARNING "==CMAKE_CURRENT_LIST_DIR====2: "${CMAKE_CURRENT_LIST_DIR})

