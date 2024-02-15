add_subdirectory(utils)
add_subdirectory(core)

add_executable(exe main.cpp)
target_link_libraries(exe PRIVATE exe_flags pthread Renderer Camera Scene Math Material Color Image Random Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Core)
