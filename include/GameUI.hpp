#ifndef GAME_UI_HPP
#define GAME_UI_HPP

#include <SFML/Graphics.hpp>

class GameUI {
public:
    GameUI();
    void render(sf::RenderWindow& window, int score, bool isPaused);
    bool isMenuButtonClicked(const sf::Vector2i& mousePosition) const;

private:
    sf::RectangleShape menuButton;
    sf::Font font;
    sf::Text menuButtonText;
    sf::Text scoreText;
    sf::Text pauseText;
};

#endif // GAME_UI_HPP