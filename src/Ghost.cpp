#include "Ghost.hpp"
#include "Constants.hpp"
#include <cmath>
#include <cstdlib>

Ghost::Ghost(float x, float y)
    : Entity(x, y, Constants::GHOST_STEP_SIZE), direction(0.0f, 0.0f), steps(0) {
    shape.setRadius(Constants::GHOST_SIZE / 2);
    shape.setOrigin(Constants::GHOST_SIZE / 2, Constants::GHOST_SIZE / 2);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Red);
    changeDirection();
}

void Ghost::changeDirection() {
    int dir = std::rand() % 4;
    switch (dir) {
        case 0: direction = sf::Vector2f(1.0f, 0.0f); break; // Right
        case 1: direction = sf::Vector2f(-1.0f, 0.0f); break; // Left
        case 2: direction = sf::Vector2f(0.0f, 1.0f); break; // Down
        case 3: direction = sf::Vector2f(0.0f, -1.0f); break; // Up
    }
}

sf::Vector2f Ghost::findNearestCell(const sf::Vector2f& targetPosition) {
    sf::Vector2f currentPosition = shape.getPosition();
    std::vector<sf::Vector2f> possibleMoves = {
        currentPosition + sf::Vector2f(Constants::GHOST_STEP_SIZE, 0),
        currentPosition + sf::Vector2f(-Constants::GHOST_STEP_SIZE, 0),
        currentPosition + sf::Vector2f(0, Constants::GHOST_STEP_SIZE),
        currentPosition + sf::Vector2f(0, -Constants::GHOST_STEP_SIZE)
    };

    sf::Vector2f nearestMove = possibleMoves[0];
    float minDistance = std::sqrt(std::pow(nearestMove.x - targetPosition.x, 2) + std::pow(nearestMove.y - targetPosition.y, 2));

    for (const auto& move : possibleMoves) {
        float distance = std::sqrt(std::pow(move.x - targetPosition.x, 2) + std::pow(move.y - targetPosition.y, 2));
        if (distance < minDistance) {
            nearestMove = move;
            minDistance = distance;
        }
    }

    return nearestMove;
}

void Ghost::update(float deltaTime, const sf::Vector2f& targetPosition, const std::vector<sf::RectangleShape>& walls) {
    moveTimer += deltaTime;

    if (moveTimer >= 0.35f) {  // Перемещение каждые 0.35 секунды
        moveTimer = 0.0f;

        sf::Vector2f movement;
        if (steps >= Constants::SMART_MOVE_INTERVAL) {
            sf::Vector2f nearestCell = findNearestCell(targetPosition);
            movement = nearestCell - shape.getPosition();
            steps = 0; // Сбрасываем счетчик шагов
        } else {
            movement = direction * speed;
            steps++;
        }

        shape.move(movement);
        bool collided = false;
        for (const auto& wall : walls) {
            if (shape.getGlobalBounds().intersects(wall.getGlobalBounds())) {
                collided = true;
                break;
            }
        }

        if (collided) {
            shape.move(-movement);
            changeDirection(); // Меняем направление при столкновении
            steps = 0; // Сбрасываем счетчик шагов
        }
    }
}

void Ghost::update(float deltaTime, const std::vector<sf::RectangleShape>& walls) {
    // Этот метод больше не нужен, но он должен быть определен, так как он объявлен в классе Entity
}

void Ghost::render(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f Ghost::getPosition() const {
    return shape.getPosition();
}