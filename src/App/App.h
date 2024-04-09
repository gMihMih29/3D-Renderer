#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "../Kernel/Kernel.h"
#include "../Utilities/GLogger.h"
#include "../View/View.h"

namespace ThreeDRenderer {

class App {
    static const int kWidth = 800;
    static const int kHeight = 600;
    static constexpr const char* kAppName = "3D Renderer";
    static const Utilities::GLogger<Utilities::ConsoleTimeSpanLoggerInstance> logger;

public:
    App();
    App(int height, int width);
    App(int height, int width, std::string name);

    void Run();

private:
    void HandleEvent_(const sf::Event& event);
    void HandleKeyEvent_(const sf::Keyboard::Key& key);
    void AddNewObject_();
    void ShowNewFrame_();

    Kernel kernel_;
    sf::RenderWindow window_;
    View view_;
};

}  // namespace ThreeDRenderer
