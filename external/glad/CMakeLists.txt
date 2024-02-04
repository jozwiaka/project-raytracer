add_library(glad STATIC glad.cpp)
target_link_libraries(glad PRIVATE exe_flags)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# PUBLIC    -> #include <glad.h>
# INTERFACE -> #include "glad.h"