# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project (3d_renderer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")


set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML COMPONENTS graphics REQUIRED)
find_package(eigen3 REQUIRED)

# Включите подпроекты.
add_subdirectory ("src")
 