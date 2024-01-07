set(App App.cpp App.h)
add_library(App ${App})

target_link_libraries(App sfml-graphics)