set(View 
    View.cpp 
    PixelScreen.cpp
    )
add_library(View ${View})
target_link_libraries(View sfml-graphics)