set(Renderer
    Renderer.cpp
    World.cpp
    Camera.cpp
    TriangularObject.cpp
    PixelScreen.cpp
    MathFuncs.cpp
    )
add_library(Renderer ${Renderer})
target_link_libraries(Renderer sfml-graphics)
target_link_libraries(Renderer Eigen3::Eigen)
target_link_libraries(Renderer Utilities)
