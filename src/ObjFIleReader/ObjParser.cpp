#include "ObjParser.h"

#include <cassert>
#include <string_view>
#include <utility>

#include "../Utilities/StringViewSplit.h"

namespace ThreeDRenderer {

Response<ObjParser::Vector3> ObjParser::ParseVector(const std::string& input) {
    Response<Vector3> response;
    std::string_view cmd(input);
    auto params = Utilities::StringViewSplit(cmd, ' ');
    if (params.size() != 3) {
        return Response<Vector3>::Error("Incorrect format of file! Not enough parameters.");
    }
    for (int i = 0; i < params.size(); ++i) {
        if (!params[i].empty() && !IsNumber_(params[i])) {
            return Response<Vector3>::Error("Incorrect format of file! Not a number.");
        }
    }
    double x = std::atof(params[0].data());
    double y = std::atof(params[1].data());
    double z = std::atof(params[2].data());
    return Response<Vector3>::Success({x, y, z});
}

Response<FaceElement> ObjParser::ParseFaceElement(const std::string& input, int vertexes_count, int normals_count) {
    std::string_view cmd(input);
    auto params = Utilities::StringViewSplit(cmd, ' ');
    if (params.size() < 3) {
        return Response<FaceElement>::Error("Incorrect format of file! Not enough parameters.");
    }
    FaceElement face;
    for (int i = 0; i < params.size(); ++i) {
        auto vertex_data = Utilities::StringViewSplit(params[i], '/');
        int vertex_index = 0;
        vertex_index = std::atoi(vertex_data[0].data());
        face.points.push_back(vertex_index);
        if (vertex_data.size() == 3) {
            int normal_vector_index = std::atoi(vertex_data[2].data());
            face.normals.push_back(normal_vector_index);
        }
    }
    if (vertexes_count == 0) {
        return Response<FaceElement>::Error("Incorrect format of file! No vertexes were found.");
    }
    if (normals_count == 0 && face.normals.size() != 0) {
        return Response<FaceElement>::Error("Incorrect format of file! No normal vectors were found.");
    }
    if (!face.normals.empty() && face.points.size() != face.normals.size()) {
        return Response<FaceElement>::Error(
            "Incorrect format of file! Illegal statement. You must be consistent in the way you reference the vertex "
            "data.");
    }
    for (int i = 0; i < face.points.size(); ++i) {
        if (face.points[i] < 0) {
            face.points[i] += vertexes_count;
        } else {
            --face.points[i];
        }
        if (face.points[i] < 0 || vertexes_count < face.points[i]) {
            return Response<FaceElement>::Error("Incorrect format of file! Index of vertex out of range.");
        }
    }
    for (int i = 0; i < face.normals.size(); ++i) {
        if (face.normals[i] < 0) {
            face.normals[i] += normals_count;
        } else {
            --face.normals[i];
        }
        if (face.normals[i] < 0 || normals_count < face.normals[i]) {
            return Response<FaceElement>::Error("Incorrect format of file! Index of normals out of range.");
        }
    }
    return Response<FaceElement>::Success(std::move(face));
}

bool ObjParser::IsNumber_(std::string_view str) {
    bool has_dot = false;
    bool has_sign = false;
    bool met_digit = false;
    for (char c : str) {
        if ('0' <= c && c <= '9') {
            met_digit = true;
            continue;
        }
        if (!has_dot && c == '.') {
            has_dot = true;
            continue;
        }
        if (!has_sign && c == '-' && !met_digit) {
            has_sign = true;
            continue;
        }
        return false;
    }
    return true;
}

}  // namespace ThreeDRenderer
