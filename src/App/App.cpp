#include "App.h"

#include <iostream>
#include <SFML/Graphics.hpp>

namespace ThreeDRenderer {

App::App() : view_(kWidth, kHeight) {
}

void App::Run() {
    while (view_.IsOpen()) {
        sf::Event event;
        while (view_.PollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                view_.Close();
            }
        }
    }
}

}  // namespace ThreeDRenderer
