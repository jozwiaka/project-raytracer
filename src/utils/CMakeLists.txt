find_package(glm REQUIRED)

file(GLOB SOURCES "./*.cpp")

add_library(utils STATIC ${SOURCES})
target_link_libraries(utils PUBLIC exe_flags pthread)
target_include_directories(
    utils
    PRIVATE ${GLM_INCLUDE_DIRS}
    INTERFACE "./"
    )