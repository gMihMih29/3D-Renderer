#include "ObjectParser.h"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "../Utilities/Logger.h"
#include "../Utilities/StringViewSplit.h"

namespace ThreeDRenderer {

TriangularObject ObjectParser::ParseObject(const std::string& path) const {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Troubles with opening file!");
    }
    std::string line;
    std::vector<TriangularObject::CoordinatesVector> vertexes;
    std::vector<TriangularObject::ConnectionVector> connections;
    std::vector<TriangularObject::NormalVector> normals;
    std::vector<TriangularObject::Surface> surfaces;
    int every_face_elemen_has_normal_vector = 0;
    int line_number = 0;
    while (std::getline(file, line)) {
        ++line_number;
        std::string_view cmd = line;
        if (cmd.find('#') != std::string_view::npos) {
            cmd = cmd.substr(0, cmd.find('#'));
        }
        if (cmd.empty()) {
            continue;
        }
        if (cmd[0] == 'v' && cmd[1] == ' ') {
            std::vector<std::string_view> params = Utilities::StringViewSplit(cmd.substr(2), ' ');
            if (params.size() < 3) {
                throw std::runtime_error("Incorrect format of file! Not enough parameters. Line in file: " +
                                         std::to_string(line_number));
            }
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < params[i].size(); ++j) {
                    if ('0' <= params[i][j] && params[i][j] <= '9' || params[i][j] == '.' || params[i][j] == ',' ||
                        params[i][j] == '-') {
                        continue;
                    }
                    throw std::runtime_error("Incorrect format of file! Not a number. Line in file: " +
                                             std::to_string(line_number));
                }
            }
            double x = std::atof(params[0].data());
            double y = std::atof(params[1].data());
            double z = std::atof(params[2].data());
            vertexes.emplace_back(x, y, z);
        } else if (cmd[0] == 'v' && cmd[1] == 'n' && cmd[2] == ' ') {
            std::vector<std::string_view> params = Utilities::StringViewSplit(cmd.substr(3), ' ');
            if (params.size() != 3) {
                throw std::runtime_error("Incorrect format of file! Not enough parameters. Line in file: " +
                                         std::to_string(line_number));
            }
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < params[i].size(); ++j) {
                    if ('0' <= params[i][j] && params[i][j] <= '9' || params[i][j] == '.' || params[i][j] == ',' ||
                        params[i][j] == '-') {
                        continue;
                    }
                    throw std::runtime_error("Incorrect format of file! Not a number. Line in file: " +
                                             std::to_string(line_number));
                }
            }
            double x = std::atof(params[0].data());
            double y = std::atof(params[1].data());
            double z = std::atof(params[2].data());
            normals.emplace_back(x, y, z);
        } else if (cmd[0] == 'f' && cmd[1] == ' ') {
            if (vertexes.size() == 0) {
                throw std::runtime_error("Incorrect format of file! No vertexes were found. Line in file:" +
                                         std::to_string(line_number));
            }
            std::vector<std::string_view> params = Utilities::StringViewSplit(cmd.substr(2), ' ');
            if (params.size() < 3) {
                throw std::runtime_error("Incorrect format of file! Not enough parameters. Line in file:" +
                                         std::to_string(line_number));
            }
            TriangularObject::ConnectionVector result_connection = TriangularObject::ConnectionVector();
            TriangularObject::NormalVector norm = TriangularObject::NormalVector(0, 0, 0);
            for (int i = 0; i < params.size(); ++i) {
                std::vector<std::string_view> val = Utilities::StringViewSplit(params[i], '/');
                int vertex_index = 0;
                vertex_index = std::atoi(val[0].data());
                --vertex_index;
                if (vertex_index / vertexes.size() != 0) {
                    throw std::runtime_error("Incorrect format of file! Index of vertex out of range. Line in file: " +
                                             std::to_string(line_number));
                }
                if (vertex_index < 0) {
                    vertex_index += vertexes.size();
                }
                result_connection.push_back(vertex_index);
                if (val.size() == 3) {
                    if (every_face_elemen_has_normal_vector == -1) {
                        throw std::runtime_error(
                            "Incorrect format of file! Illegal statement. You must be consistent in the way you "
                            "reference the vertex data. Line in file: " +
                            std::to_string(line_number));
                    }
                    every_face_elemen_has_normal_vector = 1;
                    int normal_vector_index = std::atoi(val[2].data());
                    --normal_vector_index;
                    if (normal_vector_index / normals.size() != 0) {
                        throw std::runtime_error(
                            "Incorrect format of file! Index of normals out of range. Line in file: " +
                            std::to_string(line_number));
                    }
                    if (normal_vector_index < 0) {
                        normal_vector_index += normals.size();
                    }
                    norm += normals[normal_vector_index];
                } else {
                    if (every_face_elemen_has_normal_vector == 1) {
                        throw std::runtime_error(
                            "Incorrect format of file! Illegal statement. You must be consistent in the way you "
                            "reference the vertex data. Line in file: " +
                            std::to_string(line_number));
                    }
                    every_face_elemen_has_normal_vector = -1;
                }
            }
            if (every_face_elemen_has_normal_vector == 1) {
                assert(!norm.isZero() && "Normal vector must be non zero.");
                for (int i = 1; i + 1 < result_connection.size(); ++i) {
                    surfaces.emplace_back(vertexes[result_connection[0]], vertexes[result_connection[1]],
                                          vertexes[result_connection[2]], norm);
                }
            } else if (every_face_elemen_has_normal_vector == -1) {
                connections.push_back(result_connection);
            }
        }
    }
    if (every_face_elemen_has_normal_vector == 0) {
        throw std::runtime_error("Incorrect format of file! There must be face elements for object");
    }
    if (every_face_elemen_has_normal_vector == 1) {
        return TriangularObject({0, 0, 0}, {0, 0, 0}, std::move(surfaces));
    }
    return TriangularObject({0, 0, 0}, {0, 0, 0}, vertexes, connections);
}

sf::Color ObjectParser::ParseColor(const std::string& input) const {
    const int kMinColorValue = 0;
    const int kMaxColorValue = 255;
    std::vector<std::string_view> params = Utilities::StringViewSplit(input, ' ');
    if (params.size() != 3) {
        throw std::runtime_error("Incorrect format of color! There must be three numbers.");
    }
    for (int i = 0; i < 3; ++i) {
        bool sign = false;
        for (char c : params[i]) {
            if ('0' <= c && c <= '9') {
                continue;
            }
            if (!sign && c == '-') {
                sign = true;
                continue;
            }
            throw std::runtime_error("Incorrect format of color! Parameter number " + std::to_string(i + 1));
        }
    }
    int red = 0;
    int green = 0;
    int blue = 0;
    red = std::atoi(params[0].data());
    green = std::atoi(params[1].data());
    blue = std::atoi(params[2].data());
    if (red < kMinColorValue || red > kMaxColorValue || green < kMinColorValue || green > kMaxColorValue ||
        blue < kMinColorValue || blue > kMaxColorValue) {
        throw std::runtime_error("Incorrect format of color!");
    }
    return sf::Color(red, green, blue);
}

TriangularObject::CoordinatesVector ObjectParser::ParsePosition(const std::string& input) const {
    std::vector<std::string_view> params = Utilities::StringViewSplit(input, ' ');
    if (params.size() != 3) {
        throw std::runtime_error("Incorrect format of position! There must be three numbers.");
    }
    for (int i = 0; i < 3; ++i) {
        bool sign = false;
        bool dot = false;
        for (char c : params[i]) {
            if ('0' <= c && c <= '9') {
                continue;
            }
            if (!dot && c == '.') {
                dot = true;
                continue;
            }
            if (!sign && c == '-') {
                sign = true;
                continue;
            }
            throw std::runtime_error("Incorrect format of position! Parameter number " + std::to_string(i + 1));
        }
    }
    double x = 0;
    double y = 0;
    double z = 0;
    x = std::atof(params[0].data());
    y = std::atof(params[1].data());
    z = std::atof(params[2].data());
    return TriangularObject::CoordinatesVector(x, y, z);
}

}  // namespace ThreeDRenderer
