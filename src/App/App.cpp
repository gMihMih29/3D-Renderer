#include "App.h"

#include <SFML/Graphics.hpp>

App::App() : view_(800, 600) {
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