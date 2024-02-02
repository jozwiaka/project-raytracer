add_executable(exe main.cpp)
# set_target_properties(exe PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(exe PRIVATE pthread glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glad exe_flags)
target_include_directories(exe PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

