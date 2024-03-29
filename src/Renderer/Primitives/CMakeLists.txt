set(Primitives
    TriangularObject.cpp
    Triangle.cpp
    )
add_library(Primitives ${Primitives})
target_link_libraries(Primitives sfml-graphics)
target_link_libraries(Primitives Eigen3::Eigen)
target_link_libraries(Primitives Utilities)
target_link_libraries(Primitives MathFuncs)
target_link_libraries(Primitives Light)
