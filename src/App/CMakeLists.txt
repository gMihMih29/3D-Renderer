set(App
    App.cpp
    ObjectParser.cpp
    )
add_library(App ${App})

link_directories("../Kernel")
target_link_libraries(App Kernel)

link_directories("../View")
target_link_libraries(App View)

link_directories("../../SFML/include")
target_link_libraries(App sfml-graphics)

link_directories("../Utilities")
target_link_libraries(App Utilities)

link_directories("../Renderer")
target_link_libraries(App Renderer)