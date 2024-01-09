#pragma once

#include <SFML/Graphics.hpp>

#include "../Observer/Observer.h"
#include "../View/PixelScreen.h"

class View : public CObserver<PixelScreen> {
public:
    View() = delete;
    View(int window_width, int window_height);
    bool IsOpen();
    bool PollEvent(sf::Event& event);
    void Close();
    void Draw(const PixelScreen& ps);

private:
    sf::RenderWindow window_;
};