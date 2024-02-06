#include "App.h"

#include <iostream>
#include <utility>

namespace ThreeDRenderer {

App::App() : App(kWidth, kHeight) {
}

App::App(int width, int height)
    : window_(sf::RenderWindow(sf::VideoMode(kWidth, kHeight), "3D Renderer")), view_(&window_) {
    width_ = width;
    height_ = height;
}

App::App(int width, int height, std::string name) : App(width, height) {
}

void App::Run() {
    while (window_.isOpen()) {
        sf::Event event;
        bool flag = false;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_.close();
            }
        }
        view_.Draw(k.GetScene(width_, height_));
    }
}

}  // namespace ThreeDRenderer
