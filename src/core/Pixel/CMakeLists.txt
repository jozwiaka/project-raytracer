add_library(Pixel STATIC Pixel.cpp)
target_link_libraries(Pixel PUBLIC exe_flags Color)
target_include_directories(
    Pixel
    INTERFACE "./"
    )