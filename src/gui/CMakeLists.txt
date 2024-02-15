set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

add_executable(exe_gui ${PROJECT_SOURCES})


target_link_libraries(exe_gui PRIVATE exe_flags pthread Renderer Camera Scene Math Material Color Image Random Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Core)

