cmake_minimum_required(VERSION 3.16)
project(project-raytracer LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)

add_library(exe_flags INTERFACE)
target_compile_features(exe_flags INTERFACE cxx_std_20)
target_compile_options(exe_flags INTERFACE
  "$<$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:$<BUILD_INTERFACE:-W3>>"
)

# include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(tests)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "raytracer")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "Your Name <your.email@example.com>")
set(CPACK_PACKAGE_DESCRIPTION "Your Raytracer Project Description")

set(CPACK_RPM_PACKAGE_REQUIRES "gcc, libstdc++6, libc6, libglfw3, libglfw3-dev, libglm-dev")

include(CPack)

install(TARGETS exe DESTINATION bin)