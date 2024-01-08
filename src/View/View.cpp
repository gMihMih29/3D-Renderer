#include "View.h"

View::View(int windowWidth, int windowHeight)
    : window_(sf::VideoMode(windowWidth, windowHeight), "3D-Renderer", sf::Style::Default ^ sf::Style::Resize) {
    window_.clear();
    window_.display();
}

bool View::IsOpen() {
    return window_.isOpen();
}

bool View::PollEvent(sf::Event& event) {
    return window_.pollEvent(event);
}

void View::Close() {
    window_.close();
}