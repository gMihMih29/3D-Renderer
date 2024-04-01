#include "ObjFileReader.h"

#include "ObjParser.h"
#include "TriangulatedObjectBuilder.h"

namespace ThreeDRenderer {

TriangulatedObject ObjFileReader::ReadFile(const std::string& path_to_file) {
    std::ifstream file(path_to_file);
    if (!file.is_open()) {
        throw std::runtime_error("Troubles with opening file!");
    }
    int line_number = 0;
    try {
        std::string line;
        TriangulatedObjectBuilder builder;
        while (std::getline(file, line)) {
            line = line.substr(0, line.find('#'));
            if (line.empty()) {
                continue;
            }
            if (line.size() > 2 && line[0] == 'v' && line[1] == ' ') {
                line = line.substr(line.find(' ') + 1);
                builder.AddVertex(ObjParser::ParseVector(line));
                continue;
            }
            if (line.size() > 3 && line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
                line = line.substr(line.find(' ') + 1);
                builder.AddNormal(ObjParser::ParseVector(line));
                continue;
            }
            if (line.size() > 2 && line[0] == 'f' && line[1] == ' ') {
                line = line.substr(line.find(' ') + 1);
                builder.AddFaceElement(
                    ObjParser::ParseFaceElement(line, builder.GetVertexesQuatity(), builder.GetNormalsQuatity()));
                continue;
            }
        }
        return builder.Build();
    } catch (std::runtime_error& err) {
        throw std::runtime_error(err.what() + std::string(" Line number: ") + std::to_string(line_number));
    }
}

}  // namespace ThreeDRenderer