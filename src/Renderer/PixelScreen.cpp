#include "PixelScreen.h"

namespace ThreeDRenderer {

PixelScreen::PixelScreen(int width, int height) : width_(width), height_(height), screen_(sf::PrimitiveType::Points) {
    screen_.resize(width_ * height_);
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            Pixel(i, j).color = sf::Color(0, 0, 0);
            Pixel(i, j).position = sf::Vector2f(j, i);
        }
    }
}

sf::Vertex& PixelScreen::Pixel(int row, int column) {
    return screen_[column + row * kWidth];
}

const sf::Vertex& PixelScreen::Pixel(int row, int column) const {
    return screen_[column + row * kWidth];
}

int PixelScreen::GetHeight() const {
    return height_;
}

int PixelScreen::GetWidth() const {
    return width_;
}

const PixelScreen::Pixels& PixelScreen::GetPixels() const {
    return screen_;
}

}  // namespace ThreeDRenderer
