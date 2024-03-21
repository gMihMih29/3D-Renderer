#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "../Kernel/Kernel.h"
#include "../Renderer/PixelScreen.h"
#include "../Utilities/Logger.h"
#include "../View/View.h"

namespace ThreeDRenderer {

class App {
    static const int kWidth = 800;
    static const int kHeight = 600;

public:
    App();
    App(int width, int height);
    App(int width, int height, std::string name);
    void Run();

private:

    int width_;
    int height_;
    Kernel k;
    sf::RenderWindow window_;
    View view_;
};

}  // namespace ThreeDRenderer
