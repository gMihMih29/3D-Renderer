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
    sf::Vertex& Pixel(int row, int column);
    const sf::Vertex& Pixel(int row, int column) const;
    int GetWidth() const;
    int GetHeight() const;
    const PixelScreen::Pixels& GetPixels() const;

private:
    int width_ = kWidth;
    int height_ = kHeight;
    Pixels screen_;
};

}  // namespace ThreeDRenderer
