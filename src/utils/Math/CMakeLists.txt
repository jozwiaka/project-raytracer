add_library(Math STATIC Math.cpp)
target_link_libraries(Math PUBLIC exe_flags)
target_include_directories(
    Math
    INTERFACE "./"
    PRIVATE ${GLM_INCLUDE_DIRS})