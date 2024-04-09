#include "App.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include "../UserDialog/AddNewObjectDialog.h"
#include "../Utilities/StringViewSplit.h"
#include "../Utilities/Timer.h"

namespace ThreeDRenderer {

App::App() : App(kHeight, kWidth) {
}

App::App(int height, int width) : App(height, width, kAppName) {
}

App::App(int height, int width, std::string name)
    : kernel_(height, width),
      window_(sf::RenderWindow(sf::VideoMode(width, height), kAppName, sf::Style::Titlebar | sf::Style::Close)),
      view_(&window_) {
}

void App::Run() {
    ShowNewFrame_();
    while (window_.isOpen()) {
        sf::Event event;
        while (window_.pollEvent(event)) {
            HandleEvent_(event);
        }
    }
}

void App::HandleEvent_(const sf::Event& event) {
    if (event.type == sf::Event::GainedFocus) {
        ShowNewFrame_();
    }
    if (event.type == sf::Event::KeyPressed) {
        HandleKeyEvent_(event.key.code);
    }
    if (event.type == sf::Event::Closed) {
        window_.close();
    }
}

void App::HandleKeyEvent_(const sf::Keyboard::Key& key) {
    switch (key) {
        case sf::Keyboard::Key::Escape:
            window_.close();
            return;
        case sf::Keyboard::Key::P:
            AddNewObject_();
            ShowNewFrame_();
            break;
        case sf::Keyboard::Key::W:
            kernel_.MoveCameraForward();
            ShowNewFrame_();
            break;
        case sf::Keyboard::Key::A:
            kernel_.MoveCameraLeft();
            ShowNewFrame_();
            break;
        case sf::Keyboard::Key::S:
            kernel_.MoveCameraBackwads();
            ShowNewFrame_();
            break;
        case sf::Keyboard::Key::D:
            kernel_.MoveCameraRight();
            ShowNewFrame_();
            break;
        case sf::Keyboard::Key::Up:
            kernel_.RotateCameraUp();
            ShowNewFrame_();
            break;
        case sf::Keyboard::Key::Left:
            kernel_.RotateCameraLeft();
            ShowNewFrame_();
            break;
        case sf::Keyboard::Key::Down:
            kernel_.RotateCameraDown();
            ShowNewFrame_();
            break;
        case sf::Keyboard::Key::Right:
            kernel_.RotateCameraRight();
            ShowNewFrame_();
            break;
        default:
            break;
    }
}

void App::AddNewObject_() {
    AddNewObjectDialog dialog;
    if (dialog.ReadPathToObject() && dialog.ReadObjectColor() && dialog.ReadObjectCoordinates() &&
        dialog.AddObjectToKernel(kernel_)) {
        logger.Info("New object was added successfully!");
    } else {
        logger.Info("The program continues to work.");
    }
}

void App::ShowNewFrame_() {
    Utilities::Timer t;
    view_.Draw(kernel_.MakeScene());
    logger.Info("New frame was rendered in " + std::to_string(t.GetMilliseconds()) + " millisecond.");
}

}  // namespace ThreeDRenderer
