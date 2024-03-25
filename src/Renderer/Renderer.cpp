#include "Renderer.h"

#include "../Utilities/Logger.h"

namespace ThreeDRenderer {

PixelScreen Renderer::Render(World w, Camera c) {
    PixelScreen ps = PixelScreen(c.GetWidth(), c.GetHeight());
    int k = 0;
    for (int i = 0; i < ps.GetHeigth(); ++i) {
        for (int j = 0; j < ps.GetWidth(); ++j) {
            ps.GetPixel(j, i).color = sf::Color(k % 256, k / 256 % 256, k / 256 / 256 % 256);
            ++k;
        }
    }
    return ps;
}

}  // namespace ThreeDRenderer
