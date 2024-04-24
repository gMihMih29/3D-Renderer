#include "ObjFileReader.h"

#include "ObjParser.h"
#include "TriangulatedObjectBuilder.h"

namespace ThreeDRenderer {

ObjFileReader::Response ObjFileReader::ReadFile(const std::string& path_to_file) {
    std::ifstream file(path_to_file);
    if (!file.is_open()) {
        return Response::Error("Troubles with opening file!");
    }
    int line_number = 1;
    std::string line;
    TriangulatedObjectBuilder builder;
    while (std::getline(file, line)) {
        line = line.substr(0, line.find('#'));
        if (line.empty()) {
        } else if (line.size() > 2 && line[0] == 'v' && line[1] == ' ') {
            line = line.substr(line.find(' ') + 1);
            auto response = ObjParser::ParseVector(line);
            if (response.IsSuccess()) {
                builder.AddVertex(std::move(response.GetResultObject()));
            } else {
                return Response::Error(response.GetMessage() + std::string(" Line number: ") +
                                       std::to_string(line_number));
            }
        } else if (line.size() > 3 && line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
            line = line.substr(line.find(' ') + 1);
            auto response = ObjParser::ParseVector(line);
            if (response.IsSuccess()) {
                builder.AddNormal(std::move(response.GetResultObject()));
            } else {
                return Response::Error(response.GetMessage() + std::string(" Line number: ") +
                                       std::to_string(line_number));
            }
        } else if (line.size() > 2 && line[0] == 'f' && line[1] == ' ') {
            line = line.substr(line.find(' ') + 1);
            auto response =
                ObjParser::ParseFaceElement(line, builder.GetVertexesQuatity(), builder.GetNormalsQuatity());
            if (response.IsSuccess()) {
                builder.AddFaceElement(std::move(response.GetResultObject()));
            } else {
                return Response::Error(response.GetMessage() + std::string(" Line number: ") +
                                       std::to_string(line_number));
            }
        }
        ++line_number;
    }
    return builder.Build();
}

}  // namespace ThreeDRenderer
