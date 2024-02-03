add_library(Renderer STATIC Renderer.cpp)
# target_link_libraries(Renderer PUBLIC Scene Light Material Camera Image Object Ray)
target_include_directories(Renderer INTERFACE "./")
# target_include_directories(Renderer PUBLIC "../../utils/Math")