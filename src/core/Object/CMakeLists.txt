add_library(Object STATIC Object.cpp Sphere.cpp Cuboid.cpp Cylinder.cpp)
target_link_libraries(Object PUBLIC exe_flags Math Ray Material HitRecord Interval)
target_include_directories(
    Object
    INTERFACE "./"
    )