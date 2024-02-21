add_executable(exe_nogui main.cpp MainWindow.cpp)
target_link_libraries(exe_nogui PRIVATE exe_flags pthread core glfw)
