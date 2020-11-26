
#aux_source_directory(${CMAKE_CURRENT_LIST_DIR} FILE_SHAPEOBJ)

file(GLOB FILE_SHAPEOBJ ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
add_library(shapeobj
        STATIC
        ${FILE_SHAPEOBJ})
target_link_libraries(shapeobj
        FreeImage
        yuv
)