add_library(Ray STATIC Ray.cpp)
# target_link_libraries(Ray PRIVATE )
target_include_directories(
    Ray
    INTERFACE "./"
    PRIVATE "../../utils/Math")