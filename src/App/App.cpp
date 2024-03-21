#include "App.h"

#include <iostream>
#include <utility>

namespace ThreeDRenderer {

Utilities::Logger App::console = Utilities::Logger(true);
Utilities::Logger App::logger = Utilities::Logger("../logs/" + GetCurrentDay_() + ".log", true);

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

std::string App::GetCurrentDay_() {
    std::string res;
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    res += std::to_string(now->tm_year + 1900);
    res += '-';
    if (now->tm_mon < 10) {
        res += '0';
    }
    res += std::to_string(now->tm_mon);
    res += '-';
    if (now->tm_mday < 10) {
        res += '0';
    }
    res += std::to_string(now->tm_mday);
    return res;
}


}  // namespace ThreeDRenderer
