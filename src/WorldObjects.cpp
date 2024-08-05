#include "WorldObjects.hpp"
#include "Constants.hpp"
#include <cmath>
#include <algorithm>

WorldObjects::WorldObjects(float cellSize, const std::vector<sf::RectangleShape>& walls)
    : cellSize(cellSize), walls(walls) {
    float pointRadius = Constants::POINT_RADIUS; // Радиус шариков из константы

    for (int y = 0; y < Constants::WINDOW_HEIGHT; ++y) {
        for (int x = 0; x < Constants::WINDOW_WIDTH; ++x) {
            sf::Vector2f position(x * cellSize + cellSize / 2, y * cellSize + cellSize / 2);
            if (isPositionValid(position, pointRadius)) {
                sf::CircleShape point(pointRadius);
                point.setFillColor(sf::Color::White);
                point.setPosition(position.x - pointRadius, position.y - pointRadius);
                points.push_back(point);
            }
        }
    }
}

bool WorldObjects::isPositionValid(const sf::Vector2f& position, float radius) const {
    sf::CircleShape tempShape(radius);
    tempShape.setPosition(position.x - radius, position.y - radius);
    for (const auto& wall : walls) {
        if (tempShape.getGlobalBounds().intersects(wall.getGlobalBounds())) {
            return false;
        }
    }
    return true;
}

void WorldObjects::update(const sf::Vector2f& pacmanPosition, int& score) {
    float pacmanRadius = Constants::PACMAN_SIZE / 2.0f;

    auto it = points.begin();
    while (it != points.end()) {
        float dx = pacmanPosition.x - (it->getPosition().x + it->getRadius());
        float dy = pacmanPosition.y - (it->getPosition().y + it->getRadius());
        float distance = std::sqrt(dx * dx + dy * dy);
        if (distance < pacmanRadius) {
            ++score;
            it = points.erase(it);
        } else {
            ++it;
        }
    }
}

void WorldObjects::render(sf::RenderWindow& window) {
    for (const auto& point : points) {
        window.draw(point);
    }
}