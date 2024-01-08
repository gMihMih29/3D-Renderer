set(View 
    View.h
    View.cpp 
    PixelScreen.h
    PixelScreen.cpp
    )
add_library(View ${View})
target_link_libraries(View sfml-graphics)