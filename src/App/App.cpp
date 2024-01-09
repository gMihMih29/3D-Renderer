#include "App.h"

#include <iostream>
#include <SFML/Graphics.hpp>

App::App() : view_(kWidth, kHeight) {
}

void App::Run() {
    PixelScreen ps = PixelScreen(kWidth, kHeight);
    int k = 0;
    for (int i = 0; i < ps.GetHeigth(); ++i) {
        for (int j = 0; j < ps.GetWidth(); ++j) {
            ps.GetPixel(j, i).color = sf::Color(k % 256, k / 256 % 256, k / 256 / 256 % 256);
            ++k;
        }
    }
    while (view_.IsOpen()) {
        sf::Event event;
        while (view_.PollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                view_.Close();
            }
        }
        view_.Draw(ps);
    }
}