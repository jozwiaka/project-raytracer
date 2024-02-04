add_library(Light STATIC Light.cpp)
target_include_directories(
    Light
    INTERFACE "./"
    PUBLIC "../../utils/Math")