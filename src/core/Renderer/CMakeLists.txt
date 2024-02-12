add_library(Renderer STATIC Renderer.cpp)
target_link_libraries(Renderer PUBLIC
    exe_flags
    pthread
    glfw
    ${OPENGL_LIBRARIES}
    GLEW::GLEW
    Math
    Random
    Interval
    Color
    Ray
    Material
    Light
    Object
    Scene
    Camera
    HitRecord
    )
target_include_directories(
    Renderer
    INTERFACE "./"
    PUBLIC ${GLEW_INCLUDE_DIRS})