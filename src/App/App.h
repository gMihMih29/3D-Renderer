#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "../Kernel/Kernel.h"
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
    void ChooseOption_(const sf::Event& event);
    void AddNewObject_();

    int width_;
    int height_;
    Kernel kernel_;
    sf::RenderWindow window_;
    View view_;
};

}  // namespace ThreeDRenderer
