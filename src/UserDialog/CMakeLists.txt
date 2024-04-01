set(UserDialog
    AddNewObjectDialog.cpp
    )
add_library(UserDialog ${UserDialog})

link_directories("../Kernel")
target_link_libraries(UserDialog Kernel)

link_directories("../../SFML/include")
target_link_libraries(UserDialog sfml-graphics)

link_directories("../Utilities")
target_link_libraries(UserDialog Utilities)

link_directories("../Renderer")
target_link_libraries(UserDialog Renderer)