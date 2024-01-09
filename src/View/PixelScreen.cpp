#include "PixelScreen.h"

#include <iostream>

PixelScreen::PixelScreen() : PixelScreen(kWidth, kHeight) {
}

PixelScreen::PixelScreen(int width, int height) : width_(width), height_(height), screen_(sf::Points) {
    screen_.resize(width_ * height_);
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            GetPixel(j, i).color = sf::Color(0, 0, 0);
            GetPixel(j, i).position = sf::Vector2f(j, i);
        }
    }
}

sf::Vertex& PixelScreen::GetPixel(int x, int y) {
    return screen_[x + y * kWidth];
}

const sf::Vertex& PixelScreen::GetPixel(int x, int y) const {
    return screen_[x + y * kWidth];
}

int PixelScreen::GetHeigth() const {
    return height_;
}

int PixelScreen::GetWidth() const {
    return width_;
}

const PixelScreen::Pixels& PixelScreen::GetPixels() const {
    return screen_;
}