add_library(Color STATIC ColorManipulator.cpp)
target_link_libraries(Color PUBLIC exe_flags Math Interval)
target_include_directories(
    Color
    INTERFACE "./"
    )