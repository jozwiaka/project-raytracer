add_library(Math STATIC Math.cpp)
target_include_directories(
    Math
    INTERFACE "./"
    PUBLIC ${GLM_INCLUDE_DIRS})