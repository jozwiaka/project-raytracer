add_executable(exe main.cpp)
target_link_libraries(exe PRIVATE exe_flags pthread Renderer Camera Scene Math Material Color Image Random)
