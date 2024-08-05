#include <SFML/Graphics.hpp>
#include "PacMan.hpp"
#include "Ghost.hpp"
#include "Level.hpp"
#include "GameUI.hpp"
#include "WorldObjects.hpp"
#include "Constants.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

int main() {
    Level level;
    GameUI gameUI;
    WorldObjects worldObjects(Constants::CELL_SIZE, level.getWalls());
    sf::RenderWindow window(sf::VideoMode(Constants::WINDOW_WIDTH * Constants::CELL_SIZE, Constants::WINDOW_HEIGHT * Constants::CELL_SIZE), "Pac-Man with Ghosts");

    const float cellSize = Constants::CELL_SIZE;

    sf::Vector2i pacManSpawnCell = level.getPacManSpawn();
    sf::Vector2f pacManSpawn(pacManSpawnCell.x * cellSize + cellSize / 2.0f, pacManSpawnCell.y * cellSize + cellSize / 2.0f);
    std::cout << "Pac-Man spawn position: (" << pacManSpawn.x << ", " << pacManSpawn.y << ")\n";
    PacMan pacman(pacManSpawn.x, pacManSpawn.y);

    std::vector<Ghost> ghosts;
    for (const auto& ghostSpawnCell : level.getGhostSpawns()) {
        sf::Vector2f ghostSpawn(ghostSpawnCell.x * cellSize + cellSize / 2.0f, ghostSpawnCell.y * cellSize + cellSize / 2.0f);
        std::cout << "Ghost spawn position: (" << ghostSpawn.x << ", " << ghostSpawn.y << ")\n";
        ghosts.emplace_back(ghostSpawn.x, ghostSpawn.y);
    }

    int score = 0;
    bool isPaused = false;

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (gameUI.isMenuButtonClicked(mousePosition)) {
                    isPaused = !isPaused;
                }
            }
        }

        if (!isPaused) {
            pacman.handleInput();

            float deltaTime = clock.restart().asSeconds();
            pacman.update(deltaTime, level.getWalls());

            for (auto& ghost : ghosts) {
                ghost.update(deltaTime, pacman.getPosition(), level.getWalls()); // Передача координат Pac-Man
            }

            worldObjects.update(pacman.getPosition(), score);
        } else {
            clock.restart(); // Чтобы время не шло на паузе
        }

        window.clear();
        level.render(window);
        worldObjects.render(window);
        gameUI.render(window, score, isPaused);
        pacman.render(window);
        for (auto& ghost : ghosts) {
            ghost.render(window);
        }
        window.display();
    }

    return 0;
}