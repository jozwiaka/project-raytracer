add_library(Object STATIC Object.cpp Sphere.cpp Cuboid.cpp)
target_link_libraries(Object PUBLIC exe_flags Ray Material Math)
target_include_directories(
    Object
    INTERFACE "./"
    PUBLIC ${GLM_INCLUDE_DIRS})