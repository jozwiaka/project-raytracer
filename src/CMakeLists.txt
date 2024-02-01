cmake_minimum_required(VERSION 3.22)
project(project-raytracer LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_DEBUG_POSTFIX d)

# exe flags
add_library(exe_flags INTERFACE)
target_compile_features(exe_flags INTERFACE cxx_std_23)
target_compile_options(exe_flags INTERFACE
  "$<$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:$<BUILD_INTERFACE:-W3>>"
)

# packages
find_package(OpenGL REQUIRED)

# subdirs
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
add_subdirectory(thirdparty)

# exe
add_executable(exe main.cpp)
# set_target_properties(exe PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(exe PRIVATE pthread glfw ${OPENGL_LIBRARIES} glad exe_flags)
target_include_directories(exe PRIVATE ${OPENGL_INCLUDE_DIRS})

# tests
# enable_testing()
# include(CTest)
# find_program(MEMORYCHECK_COMMAND valgrind)
# if(MEMORYCHECK_COMMAND)
#     set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes" "--leak-check=full")
#     add_test(NAME ValgrindTest COMMAND ${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS} $<TARGET_FILE:exe>)
#     set_tests_properties(ValgrindTest PROPERTIES PASS_REGULAR_EXPRESSION "ERROR SUMMARY: 0 errors from 0 contexts")
# endif()
