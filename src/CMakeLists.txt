cmake_minimum_required(VERSION 3.20)
project(projectName LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_BUILD_TYPE "Debug")
find_package(OpenGL REQUIRED)

add_executable(exe main.cpp)

target_link_libraries(exe PRIVATE pthread)

target_include_directories(exe PRIVATE ${OPENGL_INCLUDE_DIRS})
target_link_libraries(exe PRIVATE glfw ${OPENGL_LIBRARIES})

enable_testing()

# include(CTest)
# find_program(MEMORYCHECK_COMMAND valgrind)
# if(MEMORYCHECK_COMMAND)
#     set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes" "--leak-check=full")
#     add_test(NAME ValgrindTest COMMAND ${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS} $<TARGET_FILE:exe>)
#     set_tests_properties(ValgrindTest PROPERTIES PASS_REGULAR_EXPRESSION "ERROR SUMMARY: 0 errors from 0 contexts")
# endif()
