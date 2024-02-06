#include "Kernel.h"

namespace ThreeDRenderer {

Kernel::Kernel() {
}

PixelScreen Kernel::GetScene(int width, int heigth) {
    PixelScreen ps = PixelScreen(width, heigth);
    int k = 0;
    for (int i = 0; i < ps.GetHeigth(); ++i) {
        for (int j = 0; j < ps.GetWidth(); ++j) {
            ps.GetPixel(j, i).color = sf::Color(k % 256, k / 256 % 256, k / 256 / 256 % 256);
            ++k;
        }
    }
    return ps;
}

}
