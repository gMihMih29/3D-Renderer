set(Renderer
    Camera.cpp
    MathFuncs.cpp
    PixelScreen.cpp
    Renderer.cpp
    TriangularObject.cpp
    Triangle.cpp
    World.cpp
    )
add_library(Renderer ${Renderer})
target_link_libraries(Renderer sfml-graphics)
target_link_libraries(Renderer Eigen3::Eigen)
target_link_libraries(Renderer Utilities)
