#include "App.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include "../Utilities/Logger.h"
#include "../Utilities/StringViewSplit.h"
#include "../Utilities/Timer.h"
#include "ObjectParser.h"

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
        Utilities::Logger::kConsole.Info("New frame was rendered in " + std::to_string(t.GetTime()) + " millisecond.");
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
        Utilities::Logger::kConsole.Info("Key " + std::to_string(event.key.code) + " was pressed!");
        if (event.key.code == sf::Keyboard::Key::Escape) {
            window_.close();
            return;
        }
        if (event.key.code == sf::Keyboard::Key::P) {
            AddNewObject_();
            ShowNewFrame_();
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
            kernel_.CamRotateRight();
            ShowNewFrame_();
        }
    }
    if (event.type == sf::Event::Closed) {
        window_.close();
    }
}

void App::AddNewObject_() {
    try {
        std::string input;

        Utilities::Logger::kConsole.Info("Enter path to .obj file with new object:");
        std::getline(std::cin, input);
        if (input.substr(0, 4) == "exit") {
            Utilities::Logger::kConsole.Info("The program continues to work.");
            return;
        }
        ObjectParser parser;
        TriangularObject obj = parser.ParseObject(input);

        Utilities::Logger::kConsole.Info(
            "Enter color of new object: (format: <R> <G> <B>, where R, G, B are numbers, each number is integer and "
            ">=0 and <255)");
        Utilities::Logger::kConsole.Info("Example: 128 0 255");
        std::getline(std::cin, input);
        if (input.substr(0, 4) == "exit") {
            Utilities::Logger::kConsole.Info("The program continues to work.");
            return;
        }
        obj.SetColor(parser.ParseColor(input));

        Utilities::Logger::kConsole.Info(
            "Enter position of new object: (format: <x> <y> <z>, where x, y, z are numbers)");
        Utilities::Logger::kConsole.Info("Example: 1.5 -0.5 0");
        std::getline(std::cin, input);
        if (input.substr(0, 4) == "exit") {
            Utilities::Logger::kConsole.Info("The program continues to work.");
            return;
        }
        obj.SetPosition(parser.ParsePosition(input));

        kernel_.AddObject(std::move(obj));
        Utilities::Logger::kConsole.Info("New object was added successfully!");
    } catch (std::runtime_error& e) {
        Utilities::Logger::kConsoleTimeSpan.Error(e.what());
    }
}

void App::ShowNewFrame_() {
    Utilities::Timer t;
    view_.Draw(kernel_.GetScene());
    Utilities::Logger::kConsoleTimeSpan.Info("New frame was rendered in " + std::to_string(t.GetTime()) +
                                             " millisecond.");
}

}  // namespace ThreeDRenderer
