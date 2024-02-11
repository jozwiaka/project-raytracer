add_library(Random STATIC Random.cpp)
target_link_libraries(Random PUBLIC exe_flags Math)
target_include_directories(
    Random
    INTERFACE "./"
    PRIVATE ${GLM_INCLUDE_DIRS})