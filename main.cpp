#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({400, 300}), "my player");

    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        return 1;
    }

    sf::Text text(font, "Text", 30);
    text.setPosition({20, 20});

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        window.clear();
        window.draw(text);
        window.display();
    }
}