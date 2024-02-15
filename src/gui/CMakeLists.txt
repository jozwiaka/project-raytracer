add_executable(exe_gui main_gui.cpp)
target_link_libraries(exe_gui PRIVATE exe_flags pthread Renderer Camera Scene Math Material Color Image Random Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Core)
