add_library(external STATIC glad.cpp)
target_link_libraries(external PUBLIC exe_flags)
target_include_directories(external PUBLIC "./")
# PUBLIC    -> #include <glad.h>
# INTERFACE -> #include "glad.h"