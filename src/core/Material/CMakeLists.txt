add_library(Material STATIC Material.cpp)
target_link_libraries(Material PUBLIC exe_flags Math)
target_include_directories(
    Material
    INTERFACE "./"
    )