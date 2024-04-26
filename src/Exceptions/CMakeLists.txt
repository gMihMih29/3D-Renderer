set(Exceptions
    React.cpp)
add_library(Exceptions ${Exceptions})

link_directories("../Utilities")
target_link_libraries(Exceptions Utilities)
