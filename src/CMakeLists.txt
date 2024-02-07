add_subdirectory(utils)
add_subdirectory(core)

add_executable(exe main.cpp)
target_link_libraries(exe PRIVATE pthread glfw ${OPENGL_LIBRARIES} GLEW::GLEW exe_flags Renderer)
target_include_directories(exe PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

