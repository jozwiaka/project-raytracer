add_library(Light STATIC Light.cpp)
target_link_libraries(Light PUBLIC exe_flags)
target_include_directories(
    Light
    INTERFACE "./"
    PUBLIC ${GLM_INCLUDE_DIRS})