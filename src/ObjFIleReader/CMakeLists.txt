set(ObjFileReader
    ObjFileReader.cpp
    ObjParser.cpp
    TriangulatedObjectBuilder.cpp
    )
add_library(ObjFileReader ${ObjFileReader})

link_directories("../Utilities")
target_link_libraries(ObjFileReader Utilities)

link_directories("../Renderer")
target_link_libraries(ObjFileReader Renderer)
target_link_libraries(ObjFileReader Eigen3::Eigen)