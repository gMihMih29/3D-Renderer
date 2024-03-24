#include "ObjectParser.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "../Utilities/Logger.h"

namespace ThreeDRenderer {

TriangularObject ObjectParser::Read(const std::string& path) const {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Troubles with opening file!");
    }
    std::string line;
    std::vector<TriangularObject::CoordinatesVector> vertexes;
    std::vector<TriangularObject::ConnectionVector> connections;
    std::vector<TriangularObject::NormalVector> normals;
    std::vector<TriangularObject::Surface> surfaces;
    int everyFaceElementHasNormalVector = 0;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        std::string_view cmd = line;
        if (cmd.find('#') != std::string_view::npos) {
            cmd = cmd.substr(0, cmd.find('#'));
        }
        if (cmd.empty()) {
            continue;
        }
        if (cmd[0] == 'v' && cmd[1] == ' ') {
            double x, y, z;
            std::vector<std::string_view> params = Split_(cmd.substr(2), ' ');
            if (params.size() < 3) {
                throw std::runtime_error("Incorrect format of file! Not enough parameters. Line in file: " +
                                         std::to_string(lineNumber));
            }
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < params[i].size(); ++j) {
                    if ('0' <= params[i][j] && params[i][j] <= '9' || params[i][j] == '.' || params[i][j] == ',' ||
                        params[i][j] == '-') {
                        continue;
                    }
                    throw std::runtime_error("Incorrect format of file! Not a number. Line in file: " +
                                             std::to_string(lineNumber));
                }
            }
            x = std::atof(params[0].data());
            y = std::atof(params[1].data());
            z = std::atof(params[2].data());
            vertexes.emplace_back(x, y, z);
        } else if (cmd[0] == 'v' && cmd[1] == 'n' && cmd[2] == ' ') {
            double x, y, z;
            std::vector<std::string_view> params = Split_(cmd.substr(3), ' ');
            if (params.size() != 3) {
                throw std::runtime_error("Incorrect format of file! Not enough parameters. Line in file: " +
                                         std::to_string(lineNumber));
            }
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < params[i].size(); ++j) {
                    if ('0' <= params[i][j] && params[i][j] <= '9' || params[i][j] == '.' || params[i][j] == ',' ||
                        params[i][j] == '-') {
                        continue;
                    }
                    throw std::runtime_error("Incorrect format of file! Not a number. Line in file: " +
                                             std::to_string(lineNumber));
                }
            }
            x = std::atof(params[0].data());
            y = std::atof(params[1].data());
            z = std::atof(params[2].data());
            normals.emplace_back(x, y, z);
        } else if (cmd[0] == 'f' && cmd[1] == ' ') {
            if (vertexes.size() == 0) {
                throw std::runtime_error("Incorrect format of file! No vertexes were found. Line in file:" +
                                         std::to_string(lineNumber));
            }
            std::vector<std::string_view> params = Split_(cmd.substr(2), ' ');
            if (params.size() < 3) {
                throw std::runtime_error("Incorrect format of file! Not enough parameters. Line in file:" +
                                         std::to_string(lineNumber));
            }
            TriangularObject::ConnectionVector resConnection;
            TriangularObject::NormalVector norm;
            for (int i = 0; i < params.size(); ++i) {
                std::vector<std::string_view> val = Split_(params[i], '/');
                int vertexNum, secondVertex, thirdVertex;
                vertexNum = std::atoi(val[0].data());
                --vertexNum;
                if (vertexNum / vertexes.size() != 0) {
                    throw std::runtime_error("Incorrect format of file! Index of vertex out of range. Line in file: " +
                                             std::to_string(lineNumber));
                }
                if (vertexNum < 0) {
                    vertexNum += vertexes.size();
                }
                resConnection.push_back(vertexNum);
                if (val.size() == 3) {
                    if (everyFaceElementHasNormalVector == -1) {
                        throw std::runtime_error(
                            "Incorrect format of file! Illegal statement. You must be consistent in the way you "
                            "reference the vertex data. Line in file: " +
                            std::to_string(lineNumber));
                    }
                    everyFaceElementHasNormalVector = 1;
                    int normalNumber = std::atoi(val[2].data());
                    --normalNumber;
                    if (normalNumber / normals.size() != 0) {
                        throw std::runtime_error(
                            "Incorrect format of file! Index of normals out of range. Line in file: " +
                            std::to_string(lineNumber));
                    }
                    if (normalNumber < 0) {
                        normalNumber += normals.size();
                    }
                    norm += normals[normalNumber];
                } else {
                    if (everyFaceElementHasNormalVector == 1) {
                        throw std::runtime_error(
                            "Incorrect format of file! Illegal statement. You must be consistent in the way you "
                            "reference the vertex data. Line in file: " +
                            std::to_string(lineNumber));
                    }
                    everyFaceElementHasNormalVector = -1;
                }
            }
            if (everyFaceElementHasNormalVector == 1) {
                assert(!norm.isZero() && "Normal vector must be non zero.");
                for (int i = 1; i + 1 < resConnection.size(); ++i) {
                    surfaces.emplace_back(vertexes[resConnection[0]], vertexes[resConnection[1]],
                                          vertexes[resConnection[2]], norm);
                }
            } else if (everyFaceElementHasNormalVector == -1) {
                connections.push_back(resConnection);
            }
        }
    }
    if (everyFaceElementHasNormalVector == 0) {
        throw std::runtime_error("Incorrect format of file! There must be face elements for object");
    }
    if (everyFaceElementHasNormalVector == 1) {
        return TriangularObject({0, 0, 0}, {0, 0, 0}, std::move(surfaces));
    }
    return TriangularObject({0, 0, 0}, {0, 0, 0}, vertexes, connections);
}

std::vector<std::string_view> ObjectParser::Split_(std::string_view str, char separator) const {
    std::vector<std::string_view> res;
    int size = 0;
    for (auto i : str) {
        if (i == separator) {
            ++size;
        }
    }
    res.reserve(size + 1);
    std::string_view s = str.substr(0, str.find(separator));
    while (s.size() < str.size()) {
        res.push_back(s);
        str = str.substr(str.find(separator) + 1);
        s = str.substr(0, str.find(separator));
    }
    res.push_back(str);
    return res;
}

}  // namespace ThreeDRenderer
