add_library(ThreadPool STATIC ThreadPool.cpp)
target_link_libraries(ThreadPool PUBLIC exe_flags)
target_include_directories(
    ThreadPool
    INTERFACE "./"
    PRIVATE)