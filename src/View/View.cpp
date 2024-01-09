#include "View.h"

namespace ThreeDRenderer {

View::View(int window_width, int window_height)
    : CObserver(
          DoNothing, [this](const PixelScreen& ps) { Draw(ps); }, DoNothing),
      window_(sf::VideoMode(window_width, window_height), "3D-Renderer", sf::Style::Default ^ sf::Style::Resize) {
    /////
    PixelScreen ps = PixelScreen(window_width, window_height);
    int k = 0;
    for (int i = 0; i < ps.GetHeigth(); ++i) {
        for (int j = 0; j < ps.GetWidth(); ++j) {
            ps.GetPixel(j, i).color = sf::Color(k % 256, k / 256 % 256, k / 256 / 256 % 256);
            ++k;
        }
    }
    Draw(ps);
    /////
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

}  // namespace ThreeDRenderer
