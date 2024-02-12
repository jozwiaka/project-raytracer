add_library(Color STATIC Color.cpp )
target_link_libraries(Color PUBLIC exe_flags Math)
target_include_directories(
    Color
    INTERFACE "./"
    )