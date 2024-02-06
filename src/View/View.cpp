#include "View.h"

namespace ThreeDRenderer {

View::View(sf::RenderWindow* window) : window_(window) {
}

void View::Draw(const PixelScreen& ps) {
    if (window_ == nullptr) {
        return;   
    }
    window_->clear();
    window_->draw(ps.GetPixels());
    window_->display();
}

}  // namespace ThreeDRenderer
