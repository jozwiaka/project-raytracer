cmake_minimum_required(VERSION 3.22)
project(project-raytracer LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_DEBUG_POSTFIX d)

# exe flags
add_library(exe_flags INTERFACE)
target_compile_features(exe_flags INTERFACE cxx_std_23)
target_compile_options(exe_flags INTERFACE
  "$<$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:$<BUILD_INTERFACE:-W3>>"
)

# packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
# find_package(GTest REQUIRED)

# subdirs
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
# add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(tests)

# tests
# enable_testing()
# include(CTest)
# find_program(MEMORYCHECK_COMMAND valgrind)
# if(MEMORYCHECK_COMMAND)
#     set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes" "--leak-check=full")
#     add_test(NAME ValgrindTest COMMAND ${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS} $<TARGET_FILE:exe>)
#     set_tests_properties(ValgrindTest PROPERTIES PASS_REGULAR_EXPRESSION "ERROR SUMMARY: 0 errors from 0 contexts")
# endif()
