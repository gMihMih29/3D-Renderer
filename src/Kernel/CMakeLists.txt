set(Kernel Kernel.cpp)
add_library(Kernel ${Kernel})

target_link_libraries(Kernel sfml-graphics)
target_link_libraries(Kernel Renderer)

link_directories("../Utilities")
target_link_libraries(Kernel Utilities)
