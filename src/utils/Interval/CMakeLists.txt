add_library(Interval STATIC Interval.cpp)
target_link_libraries(Interval PUBLIC exe_flags)
target_include_directories(
    Interval
    INTERFACE "./"
    )