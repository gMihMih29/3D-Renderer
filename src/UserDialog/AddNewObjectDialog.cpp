#include "AddNewObjectDialog.h"

#include "../ObjFileReader/ObjFileReader.h"
#include "../Utilities/StringViewSplit.h"

namespace ThreeDRenderer {

bool AddNewObjectDialog::ReadPathToObject() {
    std::string input;
    kLogger.Info("Enter path to .obj file with new object:");
    std::getline(std::cin, input);
    if (input.substr(0, 4) == "exit") {
        return false;
    }
    if (input.substr(input.size() - 4) != ".obj") {
        kLogger.Error("File must have .obj extention!");
        return false;
    }
    path_to_file_ = input;
    return true;
}

bool AddNewObjectDialog::ReadObjectColor() {
    std::string input;
    kLogger.Info(
        "Enter color of new object: (format: <R> <G> <B>, where R, G, B are numbers, each number is integer and "
        ">=0 and <255)");
    kLogger.Info("Example: 128 0 255");
    std::getline(std::cin, input);
    if (input.substr(0, 4) == "exit") {
        return false;
    }
    auto response = ParseColor(input);
    if (response.IsSuccess()) {
        color_ = response.GetResultObject();
        return true;
    }
    kLogger.Error(response.GetMessage());
    return false;
}

bool AddNewObjectDialog::ReadObjectCoordinates() {
    std::string input;
    kLogger.Info("Enter position of new object: (format: <x> <y> <z>, where x, y, z are real numbers)");
    kLogger.Info("Example: 1.5 -0.5 0");
    std::getline(std::cin, input);
    if (input.substr(0, 4) == "exit") {
        return false;
    }
    auto response = ParsePosition(input);
    if (response.IsSuccess()) {
        position_ = response.GetResultObject();
        return true;
    }
    kLogger.Error(response.GetMessage());
    return false;
}

bool AddNewObjectDialog::AddObjectToKernel(Kernel& ker) {
    auto response = ObjFileReader::ReadFile(path_to_file_);
    if (!response.IsSuccess()) {
        kLogger.Error(response.GetMessage());
        return false;
    }
    response.GetResultObject().SetColor(color_);
    response.GetResultObject().SetPosition(position_);
    ker.AddObject(std::move(response.GetResultObject()));
    return true;
}

AddNewObjectDialog::ResponseColor AddNewObjectDialog::ParseColor(const std::string& input) {
    const int kMinColorValue = 0;
    const int kMaxColorValue = 255;
    std::vector<std::string_view> params = Utilities::StringViewSplit(input, ' ');
    if (params.size() != 3) {
        return ResponseColor::Error("Incorrect format of color! There must be three numbers.");
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
            return ResponseColor::Error("Incorrect format of color! Parameter number " + std::to_string(i + 1));
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
        return ResponseColor::Error("Incorrect format of color!");
    }
    return ResponseColor::Success(sf::Color(red, green, blue));
}

AddNewObjectDialog::ResponseVector3 AddNewObjectDialog::ParsePosition(const std::string& input) {
    std::vector<std::string_view> params = Utilities::StringViewSplit(input, ' ');
    if (params.size() != 3) {
        return ResponseVector3::Error("Incorrect format of position! There must be three numbers.");
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
            return ResponseVector3::Error("Incorrect format of position! Parameter number " + std::to_string(i + 1));
        }
    }
    double x = 0;
    double y = 0;
    double z = 0;
    x = std::atof(params[0].data());
    y = std::atof(params[1].data());
    z = std::atof(params[2].data());
    return ResponseVector3::Success(Eigen::Vector3d(x, y, z));
}

}  // namespace ThreeDRenderer
