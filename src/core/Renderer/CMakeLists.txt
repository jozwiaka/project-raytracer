add_library(Renderer STATIC Renderer.cpp)
target_link_libraries(Renderer PRIVATE
    pthread
    glfw
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    glad
    exe_flags
    Ray
    Material
    # Light
    # Object
    Scene
    Camera
    )
target_include_directories(
    Renderer
    INTERFACE "./"
    PUBLIC ${GLUT_INCLUDE_DIRS})