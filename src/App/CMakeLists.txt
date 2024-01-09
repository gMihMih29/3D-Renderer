set(App App.cpp)
add_library(App ${App})

target_link_libraries(App sfml-graphics)

link_directories(Kernel)
target_link_libraries(App Kernel)
link_directories(View)
target_link_libraries(App View)
