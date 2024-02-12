add_library(Color STATIC Color.cpp )
target_link_libraries(Color PUBLIC exe_flags Math Interval)
target_include_directories(
    Color
    INTERFACE "./"
    )