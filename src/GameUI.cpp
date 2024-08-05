#include "GameUI.hpp"
#include "Constants.hpp"
#include <string>

GameUI::GameUI() {
    // Кнопка меню
    menuButton.setSize(Constants::MENU_BUTTON_SIZE);
    menuButton.setFillColor(Constants::MENU_BUTTON_COLOR);
    menuButton.setPosition(Constants::WINDOW_WIDTH * Constants::CELL_SIZE - Constants::MENU_BUTTON_SIZE.x, 0); // Прилегает к верхнему правому углу

    // Текст кнопки меню
    if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        throw std::runtime_error("Could not load font!");
    }

    menuButtonText.setFont(font);
    menuButtonText.setString("Menu");
    menuButtonText.setCharacterSize(24);
    menuButtonText.setFillColor(Constants::MENU_BUTTON_TEXT_COLOR);
    menuButtonText.setPosition(
        menuButton.getPosition().x + (Constants::MENU_BUTTON_SIZE.x - menuButtonText.getLocalBounds().width) / 2,
        menuButton.getPosition().y + (Constants::MENU_BUTTON_SIZE.y - menuButtonText.getLocalBounds().height) / 2 - 5
    );

    // Текст очков
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Constants::SCORE_TEXT_COLOR); // Установка черного цвета для текста счета
    scoreText.setPosition(10, 10);

    // Текст паузы
    pauseText.setFont(font);
    pauseText.setString("GAME\nPAUSED");
    pauseText.setCharacterSize(48);
    pauseText.setFillColor(Constants::PAUSE_TEXT_COLOR); // Установка черного цвета для текста паузы
    pauseText.setPosition(
        (Constants::WINDOW_WIDTH * Constants::CELL_SIZE - pauseText.getLocalBounds().width) / 2,
        (Constants::WINDOW_HEIGHT * Constants::CELL_SIZE - pauseText.getLocalBounds().height) / 2
    );
}

void GameUI::render(sf::RenderWindow& window, int score, bool isPaused) {
    window.draw(menuButton);
    window.draw(menuButtonText);

    scoreText.setString("Score: " + std::to_string(score));
    window.draw(scoreText);

    if (isPaused) {
        static sf::Clock clock;
        float time = clock.getElapsedTime().asSeconds();
        if (static_cast<int>(time * 2) % 2 == 0) { // Мигающий текст
            window.draw(pauseText);
        }
    }
}

bool GameUI::isMenuButtonClicked(const sf::Vector2i& mousePosition) const {
    return menuButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
}