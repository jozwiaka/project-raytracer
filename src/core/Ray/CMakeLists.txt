add_library(Ray STATIC Ray.cpp)
target_include_directories(
    Ray
    INTERFACE "./"
    PUBLIC ${GLM_INCLUDE_DIRS})