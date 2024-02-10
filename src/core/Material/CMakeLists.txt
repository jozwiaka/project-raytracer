add_library(Material STATIC Material.cpp Dielectric.cpp Lambertian.cpp Metal.cpp)
target_link_libraries(Material PUBLIC exe_flags Math Ray)
target_include_directories(
    Material
    INTERFACE "./"
    )