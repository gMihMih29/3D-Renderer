#pragma once

#include <SFML/Graphics.hpp>

#include "../Observer/Observer.h"
#include "../View/PixelScreen.h"

class View : public CObserver<PixelScreen> {
public:
    View() = delete;
    View(int windowWidth, int windowHeight);
    bool IsOpen();
    bool PollEvent(sf::Event& event);
    void Close();

private:
    sf::RenderWindow window_;
};