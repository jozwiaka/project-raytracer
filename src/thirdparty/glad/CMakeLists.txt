add_library(glad STATIC glad.cpp)
target_link_libraries(glad PUBLIC exe_flags)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})