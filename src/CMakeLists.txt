add_executable(${PROJECT_NAME} main.cpp)

# App
add_subdirectory("App")
link_directories(App)
target_link_libraries(${PROJECT_NAME} App)

# View
add_subdirectory("View")
link_directories(View)
target_link_libraries(${PROJECT_NAME} View)

# Kernel
add_subdirectory("Kernel")
link_directories(Kernel)
target_link_libraries(${PROJECT_NAME} Kernel)

# Observer
# add_subdirectory("Observer")
# link_directories(Observer)
# target_link_libraries(${PROJECT_NAME} Observer)