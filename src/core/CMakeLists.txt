find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB SOURCES "./*.cpp")
add_library(core STATIC ${SOURCES})
target_link_libraries(core PUBLIC
    exe_flags
    pthread
    glfw
    ${OPENGL_LIBRARIES}
    GLEW::GLEW
    external
    utils
)

target_include_directories(
    core
    PUBLIC ${GLEW_INCLUDE_DIRS}
    INTERFACE "./"
)
