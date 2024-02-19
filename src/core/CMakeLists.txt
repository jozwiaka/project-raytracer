find_package(OpenGL REQUIRED)

file(GLOB SOURCES "./*.cpp")
add_library(core STATIC ${SOURCES})
target_link_libraries(core PUBLIC
    exe_flags
    pthread
    glfw
    ${OPENGL_LIBRARIES}
    external
    utils
)

target_include_directories(
    core
    INTERFACE "./"
)
