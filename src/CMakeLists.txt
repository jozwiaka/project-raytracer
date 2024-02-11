add_subdirectory(utils)
add_subdirectory(core)

add_executable(exe main.cpp)
target_link_libraries(exe PUBLIC exe_flags pthread Renderer Camera Scene Math Material)
