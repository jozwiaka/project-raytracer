add_library(Scene STATIC Scene.cpp)
# target_link_libraries(Scene PRIVATE Ray)
target_include_directories(
    Scene
    INTERFACE "./"
    PUBLIC "../../utils/Math")