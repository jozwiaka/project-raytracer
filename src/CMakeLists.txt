# add_subdirectory(core)

# add_executable(exe main.cpp)
# target_link_libraries(exe PRIVATE pthread glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} exe_flags Renderer)
# target_include_directories(exe PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(exe vulkan.cpp)
target_link_libraries(exe PRIVATE pthread glfw Vulkan::Vulkan exe_flags)
# target_include_directories(exe PRIVATE ${VULKAN_INCLUDE_DIRS})

