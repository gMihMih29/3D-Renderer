#pragma once

#include <SFML/Graphics.hpp>

#include "../Observer/Observer.h"
#include "../View/PixelScreen.h"

namespace ThreeDRenderer {

class View {
public:
    View(int window_width, int window_height);
    CObserver<PixelScreen>* ScreenPort();

private:
    void Draw(const PixelScreen& ps);

    CObserver<PixelScreen> observer_;
    sf::RenderWindow* window_;
};

}  // namespace ThreeDRenderer
