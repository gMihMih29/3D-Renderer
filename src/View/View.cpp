#include "View.h"

namespace ThreeDRenderer {

View::View(int window_width, int window_height)
    : observer_([this](const PixelScreen& ps) { Draw(ps); }, [this](const PixelScreen& ps) { Draw(ps); },
                CObserver<PixelScreen>::DoNothing),
      window_(nullptr) {
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

CObserver<PixelScreen>* View::ScreenPort() {
    return &observer_;
}

void View::Draw(const PixelScreen& ps) {
    window_->clear();
    window_->draw(ps.GetPixels());
    window_->display();
}

}  // namespace ThreeDRenderer
