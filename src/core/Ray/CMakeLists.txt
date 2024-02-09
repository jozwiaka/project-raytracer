add_library(Ray STATIC Ray.cpp)
target_link_libraries(Ray PUBLIC exe_flags Math)
target_include_directories(
    Ray
    INTERFACE "./"
    )