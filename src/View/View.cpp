#include "View.h"

View::View(int window_width, int window_height)
    : CObserver(
          DoNothing, [this](const PixelScreen& ps) { Draw(ps); }, DoNothing),
      window_(sf::VideoMode(window_width, window_height), "3D-Renderer", sf::Style::Default ^ sf::Style::Resize) {
    window_.clear();
    window_.display();
}

bool View::IsOpen() {
    return window_.isOpen();
}

bool View::PollEvent(sf::Event& event) {
    return window_.pollEvent(event);
}

void View::Close() {
    window_.close();
}

void View::Draw(const PixelScreen& ps) {
    window_.clear();
    window_.draw(ps.GetPixels());
    window_.display();
}