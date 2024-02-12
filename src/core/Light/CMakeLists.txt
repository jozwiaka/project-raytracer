add_library(Light STATIC Light.cpp)
target_link_libraries(Light PUBLIC exe_flags Math Color)
target_include_directories(
    Light
    INTERFACE "./"
    )