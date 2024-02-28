set(Renderer
    Renderer.cpp
    World.cpp
    Camera.cpp
    TriangularObject.cpp
    )
add_library(Renderer ${Renderer})

target_link_libraries(Renderer Eigen3::Eigen)