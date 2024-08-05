#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

namespace Constants {
    const float CELL_SIZE = 50.0f; // Увеличено в 2 раза
    const float PACMAN_SIZE = 40.0f; // Увеличено в 2 раза
    const float GHOST_SIZE = 40.0f; // Увеличено в 2 раза
    const float PACMAN_STEP_SIZE = CELL_SIZE;
    const float GHOST_STEP_SIZE = CELL_SIZE;
    const float POINT_RADIUS = PACMAN_SIZE / 8.0f; // Радиус шариков в 8 раз меньше радиуса Pac-Man
    const int SMART_MOVE_INTERVAL = 3; // Число шагов до умного хода
    const int WINDOW_WIDTH = 16; // количество клеток по горизонтали
    const int WINDOW_HEIGHT = 16; // количество клеток по вертикали
    const std::string PROJECT_PATH = "/Users/ampiro/programs/PacMan"; // Установите правильный путь

    const sf::Vector2f MENU_BUTTON_SIZE(CELL_SIZE * 2, CELL_SIZE); // 2 клетки в ширину и 1 в высоту
    const sf::Color MENU_BUTTON_COLOR(200, 200, 200);
    const sf::Color MENU_BUTTON_TEXT_COLOR(0, 0, 0);

    const sf::Color PAUSE_TEXT_COLOR(242, 220, 208); // Black color for the pause text
    const sf::Color SCORE_TEXT_COLOR(0, 0, 0); // Black color for the score text
}

#endif // CONSTANTS_HPP