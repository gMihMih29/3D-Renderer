#pragma once

#include <vector>

namespace ThreeDRenderer {

struct FaceElement {
    std::vector<int> points;
    std::vector<int> normals;
};

}  // namespace ThreeDRenderer
