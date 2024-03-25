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
            std::vector<std::string_view> params = Utilities::StringViewSplit(cmd.substr(2), ' ');
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
            std::vector<std::string_view> params = Utilities::StringViewSplit(cmd.substr(3), ' ');
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
            std::vector<std::string_view> params = Utilities::StringViewSplit(cmd.substr(2), ' ');
            if (params.size() < 3) {
                throw std::runtime_error("Incorrect format of file! Not enough parameters. Line in file:" +
                                         std::to_string(lineNumber));
            }
            TriangularObject::ConnectionVector resConnection = TriangularObject::ConnectionVector();
            TriangularObject::NormalVector norm = TriangularObject::NormalVector(0, 0, 0);
            for (int i = 0; i < params.size(); ++i) {
                std::vector<std::string_view> val = Utilities::StringViewSplit(params[i], '/');
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
                    Utilities::Logger::kConsole.Info("Normal vector for surface on line" + std::to_string(lineNumber) + " :");
                    Utilities::Logger::kConsole.Log(norm);
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
                Utilities::Logger::kConsole.Info("Normal vector for surface:");
                Utilities::Logger::kConsole.Log(norm);
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

sf::Color ObjectParser::ParseColor(const std::string& input) const{
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
    int r, g, b;
    r = std::atoi(params[0].data());
    g = std::atoi(params[1].data());
    b = std::atoi(params[2].data());
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        throw std::runtime_error("Incorrect format of color!");
    }
    return sf::Color(r, g, b);
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
    double x, y, z;
    x = std::atof(params[0].data());
    y = std::atof(params[1].data());
    z = std::atof(params[2].data());
    return TriangularObject::CoordinatesVector(x, y, z);
}

}  // namespace ThreeDRenderer
