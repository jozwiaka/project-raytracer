add_library(Camera STATIC Camera.cpp)
target_link_libraries(Camera PUBLIC exe_flags Math Ray)
target_include_directories(
    Camera
    INTERFACE "./"
    )