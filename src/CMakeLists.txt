add_subdirectory(utils)
add_subdirectory(core)

add_executable(exe main.cpp)
target_link_libraries(exe PUBLIC exe_flags pthread glfw ${OPENGL_LIBRARIES} GLEW::GLEW Renderer)
target_include_directories(exe PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})


# add_executable(exe main_viewport.cpp)
# target_link_libraries(exe PUBLIC exe_flags pthread glfw ${OPENGL_LIBRARIES} GLEW::GLEW)
# target_include_directories(exe PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})