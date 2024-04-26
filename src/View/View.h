#pragma once

#include <SFML/Graphics.hpp>

#include "../Renderer/PixelScreen.h"

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
