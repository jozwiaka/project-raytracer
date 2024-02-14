add_library(Texture STATIC Texture.cpp )
target_link_libraries(Texture PUBLIC exe_flags Math Color)
target_include_directories(
    Texture
    INTERFACE "./"
    )