#include <SFML/Graphics.hpp>

class View {
public:
    View() = delete;
    View(int windowWidth, int windowHeight);
    bool IsOpen();
    bool PollEvent(sf::Event& event);
    void Close();

private:
    sf::RenderWindow window_;
};