#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace ThreeDRenderer {

inline double DegToRad(double angle) {
    return angle * M_PI / 180;
}

}  // namespace ThreeDRenderer
