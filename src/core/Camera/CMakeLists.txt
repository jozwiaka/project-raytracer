add_library(Camera STATIC Camera.cpp)
target_link_libraries(Camera PRIVATE Ray)
target_include_directories(
    Camera
    INTERFACE "./"
    PUBLIC "../../utils/Math")