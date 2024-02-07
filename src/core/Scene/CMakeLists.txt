add_library(Scene STATIC Scene.cpp)
target_link_libraries(Scene PUBLIC exe_flags Ray Object Material Light)
target_include_directories(
    Scene
    INTERFACE "./"
    PUBLIC ${GLM_INCLUDE_DIRS})