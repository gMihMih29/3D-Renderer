add_executable(${PROJECT_NAME} main.cpp)

# App
link_directories(App)
add_subdirectory("App")
target_link_libraries(${PROJECT_NAME} App)