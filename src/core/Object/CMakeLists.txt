add_library(Object STATIC Object.cpp Sphere.cpp)
target_link_libraries(Object PRIVATE Ray Material)
target_include_directories(
    Object
    INTERFACE "./"
    PUBLIC "../../utils/Math")