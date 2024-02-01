cmake_minimum_required(VERSION 3.22)
project(project-raytracer LANGUAGES CXX)

# build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# exe flags
add_library(exe_flags INTERFACE)
target_compile_features(exe_flags INTERFACE cxx_std_23)
target_compile_options(exe_flags INTERFACE
  "$<$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:$<BUILD_INTERFACE:-W3>>"
  "$<$<CONFIG:Debug>:"
      "$<$<CXX_COMPILER_ID:GNU,Clang,ARMClang,AppleClang>: -g>"
      "$<$<CXX_COMPILER_ID:MSVC>: /Zi>"
  ">"
)

# packages
find_package(OpenGL REQUIRED)

# subdirs
add_subdirectory(thirdparty)

# exe
add_executable(exe main.cpp)
target_include_directories(exe PRIVATE ${OPENGL_INCLUDE_DIRS})
target_link_libraries(exe PRIVATE exe_flags pthread glfw ${OPENGL_LIBRARIES} glad)

# tests
# enable_testing()
# include(CTest)
# find_program(MEMORYCHECK_COMMAND valgrind)
# if(MEMORYCHECK_COMMAND)
#     set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes" "--leak-check=full")
#     add_test(NAME ValgrindTest COMMAND ${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS} $<TARGET_FILE:exe>)
#     set_tests_properties(ValgrindTest PROPERTIES PASS_REGULAR_EXPRESSION "ERROR SUMMARY: 0 errors from 0 contexts")
# endif()
