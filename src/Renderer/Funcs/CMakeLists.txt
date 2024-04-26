set(MathFuncs
    MathFuncs.cpp
    )
add_library(MathFuncs ${MathFuncs})
target_link_libraries(MathFuncs Eigen3::Eigen)
target_link_libraries(MathFuncs sfml-graphics)
