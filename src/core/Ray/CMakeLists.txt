add_library(Ray STATIC Ray.cpp)
target_include_directories(
    Ray
    INTERFACE "./"
    PUBLIC "../../utils/Math")