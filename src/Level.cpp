#include "Level.hpp"
#include "Constants.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Level::Level() {
    createLevel();
}

void Level::createLevel() {
    std::ifstream levelFile(Constants::PROJECT_PATH + "/media/level.txt");
    if (!levelFile.is_open()) {
        std::cerr << "Failed to open level file: " << Constants::PROJECT_PATH + "/media/level.txt" << std::endl;
        return;
    }

    std::string line;
    int y = 0;
    while (std::getline(levelFile, line)) {
        std::istringstream iss(line);
        char cell;
        int x = 0;
        while (iss >> cell) {
            if (cell == '#') {
                sf::RectangleShape wall(sf::Vector2f(Constants::CELL_SIZE, Constants::CELL_SIZE));
                wall.setFillColor(sf::Color(173, 216, 230)); // Светло-голубой цвет
                wall.setPosition(x * Constants::CELL_SIZE, y * Constants::CELL_SIZE);
                walls.push_back(wall);
            } else if (cell == 'P') {
                pacManSpawn = sf::Vector2i(x, y);
            } else if (cell == 'G') {
                ghostSpawns.push_back(sf::Vector2i(x, y));
            }
            ++x;
        }
        ++y;
    }
}

const std::vector<sf::RectangleShape>& Level::getWalls() const {
    return walls;
}

sf::Vector2i Level::getPacManSpawn() const {
    return pacManSpawn;
}

std::vector<sf::Vector2i> Level::getGhostSpawns() const {
    return ghostSpawns;
}

void Level::render(sf::RenderWindow& window) {
    for (const auto& wall : walls) {
        window.draw(wall);
    }
}