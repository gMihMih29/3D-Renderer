set(Renderer
    PixelScreen.cpp
    Renderer.cpp
    )

add_subdirectory(Funcs)
add_subdirectory(Light)
add_subdirectory(Primitives)
add_subdirectory(World)

add_library(Renderer ${Renderer})
target_link_libraries(Renderer sfml-graphics)
target_link_libraries(Renderer Eigen3::Eigen)
target_link_libraries(Renderer Utilities)
target_link_libraries(Renderer World)
target_link_libraries(Renderer MathFuncs)
target_link_libraries(Renderer Light)
