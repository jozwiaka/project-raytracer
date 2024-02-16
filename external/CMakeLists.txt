file(GLOB SOURCES "./*.cpp")
add_library(external STATIC ${SOURCES})
# target_link_libraries(external PUBLIC exe_flags)
target_include_directories(external PUBLIC "./")