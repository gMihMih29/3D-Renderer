#pragma once

#include <SFML/Graphics.hpp>

namespace ThreeDRenderer {

class PixelScreen {
    static const int kWidth = 800;
    static const int kHeight = 600;

public:
    PixelScreen();
    PixelScreen(int height, int width);
    
    sf::Vertex& Pixel(int row, int column);
    const sf::Vertex& Pixel(int row, int column) const;

    int GetWidth() const;
    int GetHeight() const;
    const sf::VertexArray& GetPixels() const;

private:
    int width_ = kWidth;
    int height_ = kHeight;
    sf::VertexArray screen_;
};

}  // namespace ThreeDRenderer
