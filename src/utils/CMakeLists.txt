file(GLOB SOURCES "./*.cpp")
add_library(utils STATIC ${SOURCES})
target_link_libraries(utils PUBLIC exe_flags)
target_include_directories(
    utils
    INTERFACE "./"
    PRIVATE ${GLM_INCLUDE_DIRS}
    )