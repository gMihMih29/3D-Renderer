#pragma once

#include <SFML/Graphics.hpp>

namespace ThreeDRenderer {

class PixelScreen {
    using Pixels = sf::VertexArray;

    static const int kWidth = 800;
    static const int kHeight = 600;

public:
    PixelScreen() = default;
    PixelScreen(int width, int height);
    sf::Vertex& GetPixel(int x, int y);
    const sf::Vertex& GetPixel(int x, int y) const;
    int GetWidth() const;
    int GetHeigth() const;
    const PixelScreen::Pixels& GetPixels() const;

private:
    int width_ = kWidth;
    int height_ = kHeight;
    Pixels screen_;
};

}  // namespace ThreeDRenderer
