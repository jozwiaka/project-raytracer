add_executable(exe main.cpp)
target_link_libraries(exe PRIVATE exe_flags pthread core)
