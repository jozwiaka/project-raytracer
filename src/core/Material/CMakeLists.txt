add_library(Material STATIC Material.cpp)
target_include_directories(
    Material
    INTERFACE "./"
    PUBLIC "../../utils/Math")