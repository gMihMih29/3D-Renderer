#include "App.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include "../Utilities/StringViewSplit.h"
#include "../Utilities/Timer.h"
#include "ObjectParser.h"

namespace ThreeDRenderer {

App::App() : App(kWidth, kHeight) {
}

App::App(int width, int height) : App(width, height, kAppName) {
}

App::App(int width, int height, std::string name)
    : kernel_(width, height), window_(sf::RenderWindow(sf::VideoMode(width, height), kAppName)), view_(&window_) {
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
    try {
        std::string input;

        Logger::kConsole.Info("Enter path to .obj file with new object:");
        std::getline(std::cin, input);
        if (input.substr(0, 4) == "exit") {
            Logger::kConsole.Info("The program continues to work.");
            return;
        }
        ObjectParser parser;
        TriangulatedObject obj = parser.ParseObject(input);

        Logger::kConsole.Info(
            "Enter color of new object: (format: <R> <G> <B>, where R, G, B are numbers, each number is integer and "
            ">=0 and <255)");
        Logger::kConsole.Info("Example: 128 0 255");
        std::getline(std::cin, input);
        if (input.substr(0, 4) == "exit") {
            Logger::kConsole.Info("The program continues to work.");
            return;
        }
        obj.SetColor(parser.ParseColor(input));

        Logger::kConsole.Info("Enter position of new object: (format: <x> <y> <z>, where x, y, z are numbers)");
        Logger::kConsole.Info("Example: 1.5 -0.5 0");
        std::getline(std::cin, input);
        if (input.substr(0, 4) == "exit") {
            Logger::kConsole.Info("The program continues to work.");
            return;
        }
        obj.SetPosition(parser.ParsePosition(input));

        kernel_.AddObject(std::move(obj));
        Logger::kConsole.Info("New object was added successfully!");
    } catch (std::runtime_error& e) {
        Logger::kConsoleTimeSpan.Error(e.what());
    }
}

void App::ShowNewFrame_() {
    Utilities::Timer t;
    view_.Draw(kernel_.MakeScene());
    Logger::kConsoleTimeSpan.Info("New frame was rendered in " + std::to_string(t.GetMilliseconds()) + " millisecond.");
}

}  // namespace ThreeDRenderer
