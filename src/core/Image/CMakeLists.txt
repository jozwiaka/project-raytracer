add_library(Image STATIC Image.cpp)
target_link_libraries(Image PUBLIC exe_flags Pixel)
target_include_directories(
    Image
    INTERFACE "./"
    )