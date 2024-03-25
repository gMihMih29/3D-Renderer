set(World
    Camera.cpp
    World.cpp
    )
add_library(World ${World})
target_link_libraries(World Eigen3::Eigen)
target_link_libraries(World Utilities)
target_link_libraries(World Primitives)
target_link_libraries(World MathFuncs)
