add_library(Renderer STATIC Renderer.cpp)
target_link_libraries(Renderer PUBLIC pthread glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glad exe_flags) #Scene Light Material Camera Image Object Ray
target_include_directories(Renderer PUBLIC "./" ${GLUT_INCLUDE_DIRS})