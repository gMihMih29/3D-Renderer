set(View 
    View.cpp
    )
add_library(View ${View})
target_link_libraries(View sfml-graphics)
target_link_libraries(View Renderer)