add_library(Image STATIC Image.cpp)
target_include_directories(
    Image
    INTERFACE "./"
    PUBLIC "../../utils/Math")