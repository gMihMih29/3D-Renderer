set(Light
    AmbientLight.cpp
    Color.cpp
    DirectionalLight.cpp
    )

add_library(Light ${Light})
target_link_libraries(Light sfml-graphics)
target_link_libraries(Light Eigen3::Eigen)
target_link_libraries(Light MathFuncs)
target_link_libraries(Light Utilities)
