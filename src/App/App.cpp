#include "App.h"

#include <iostream>
#include <utility>

#include "../Utilities/Logger.h"
#include "../Utilities/Timer.h"

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
    {
        Utilities::Timer t;
        view_.Draw(kernel_.GetScene());
        Utilities::Logger::console.Info("New frame was rendered in " + std::to_string(t.GetTime()) + " millisecond.");
    }
    while (window_.isOpen()) {
        sf::Event event;
        bool flag = false;
        while (window_.pollEvent(event)) {
            HandleEvent_(event);
        }
    }
}

void App::HandleEvent_(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        Utilities::Logger::console.Info("Key " + std::to_string(event.key.code) + " was pressed!");
        if (event.key.code == sf::Keyboard::Key::P) {
            AddNewObject_();
            return;
        }
        if (event.key.code == sf::Keyboard::Key::Escape) {
            window_.close();
            return;
        }
        if (event.key.code == sf::Keyboard::Key::W) {
            kernel_.CamMoveForward();
            ShowNewFrame_();
        }
        if (event.key.code == sf::Keyboard::Key::A) {
            kernel_.CamMoveLeft();
            ShowNewFrame_();
        }
        if (event.key.code == sf::Keyboard::Key::S) {
            kernel_.CamMoveBackwads();
            ShowNewFrame_();
        }
        if (event.key.code == sf::Keyboard::Key::D) {
            kernel_.CamMoveRight();
            ShowNewFrame_();
        }
        if (event.key.code == sf::Keyboard::Key::Up) {
            kernel_.CamRotateUp();
            ShowNewFrame_();
        }
        if (event.key.code == sf::Keyboard::Key::Left) {
            kernel_.CamRotateLeft();
            ShowNewFrame_();
        }
        if (event.key.code == sf::Keyboard::Key::Down) {
            kernel_.CamRotateDown();
            ShowNewFrame_();
        }
        if (event.key.code == sf::Keyboard::Key::Right) {
            kernel_.CamRotateDown();
            ShowNewFrame_();
        }
    }
    if (event.type == sf::Event::Closed) {
        window_.close();
    }
}

void App::AddNewObject_() {
    Utilities::Logger::console.Info("Here will be adding new object");
}

void App::ShowNewFrame_() {
    Utilities::Timer t;
    view_.Draw(kernel_.GetScene());
    Utilities::Logger::consoleTimeSpan.Info("New frame was rendered in " + std::to_string(t.GetTime()) + " millisecond.");
}

}  // namespace ThreeDRenderer
