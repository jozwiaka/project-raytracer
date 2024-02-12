add_library(Scene STATIC Scene.cpp)
target_link_libraries(Scene PUBLIC exe_flags Math Ray Object Material Light HitRecord)
target_include_directories(
    Scene
    INTERFACE "./"
    )