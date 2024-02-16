file(GLOB SOURCES "./*.cpp")
add_library(core STATIC ${SOURCES})
target_link_libraries(core PUBLIC
    exe_flags
    utils
    glfw
    ${OPENGL_LIBRARIES}
    GLEW::GLEW
)


target_include_directories(
    core
    INTERFACE "./"
    PUBLIC ${GLEW_INCLUDE_DIRS}
)
