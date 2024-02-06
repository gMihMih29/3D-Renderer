# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project (3d_renderer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set(SFML_STATIC_LIBRARIES TRUE)

add_executable(${PROJECT_NAME} src/main.cpp)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_subdirectory(eigen)

install(TARGETS ${PROJECT_NAME})

# Включите подпроекты.
add_subdirectory(src)

add_subdirectory(src/Exceptions)
link_directories(Exceptions)

add_subdirectory(src/App)
link_directories(App)

add_subdirectory(src/Kernel)
link_directories(Kernel)

add_subdirectory(src/View)
link_directories(View)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics eigen Exceptions App)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)