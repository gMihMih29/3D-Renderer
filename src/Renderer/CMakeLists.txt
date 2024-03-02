set(Renderer
    Renderer.cpp
    World.cpp
    Camera.cpp
    TriangularObject.cpp
    PixelScreen.cpp
    )
add_library(Renderer ${Renderer})
target_link_libraries(Renderer sfml-graphics)
target_link_libraries(Renderer Eigen3::Eigen)