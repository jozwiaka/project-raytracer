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
