add_library(Image STATIC Image.cpp)
target_link_libraries(Image PUBLIC exe_flags)
target_include_directories(
    Image
    INTERFACE "./"
    PUBLIC ${GLM_INCLUDE_DIRS})