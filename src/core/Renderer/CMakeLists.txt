add_library(Renderer STATIC Renderer.cpp)
target_link_libraries(Renderer PRIVATE
    pthread
    glfw
    ${OPENGL_LIBRARIES}
    GLEW::GLEW
    exe_flags
    Ray
    Material
    Light
    Object
    Scene
    Camera
    Image
    )
target_include_directories(
    Renderer
    INTERFACE "./"
    PUBLIC ${GLEW_INCLUDE_DIRS})