#pragma once

#include "../View/PixelScreen.h"
#include <SFML/Graphics.hpp>

namespace ThreeDRenderer {

class View {
public:
    View() = default;
    explicit View(sf::RenderWindow* window);
    void Draw(const PixelScreen& ps);

private:
    sf::RenderWindow* window_ = nullptr;
};

}  // namespace ThreeDRenderer
