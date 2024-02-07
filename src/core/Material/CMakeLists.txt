add_library(Material STATIC Material.cpp)
target_include_directories(
    Material
    INTERFACE "./"
    PUBLIC ${GLM_INCLUDE_DIRS})