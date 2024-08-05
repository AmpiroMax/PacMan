#include "PacMan.hpp"
#include "Constants.hpp"
#include <cmath>

PacMan::PacMan(float x, float y)
    : Entity(x, y, Constants::PACMAN_STEP_SIZE), direction(0.0f, 0.0f), mouthOpen(false), mouthTimer(0.0f), rotationAngle(0.0f) {
    shape.setPointCount(30);
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(Constants::PACMAN_SIZE / 2.0f, Constants::PACMAN_SIZE / 2.0f); // Установим центр в середину
    shape.setPosition(x, y);
    updateShape();
}

void PacMan::handleInput() {
    sf::Vector2f newDirection(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        newDirection.y = -1.0f;
        newDirection.x = 0.0f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        newDirection.y = 1.0f;
        newDirection.x = 0.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        newDirection.x = -1.0f;
        newDirection.y = 0.0f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        newDirection.x = 1.0f;
        newDirection.y = 0.0f;
    }

    if (newDirection.x != 0.0f || newDirection.y != 0.0f) {
        direction = newDirection;
        float angle = std::atan2(direction.y, direction.x);
        rotationAngle = angle * 180.0f / 3.14f + 180.0f;
    }
}

void PacMan::update(float deltaTime, const std::vector<sf::RectangleShape>& walls) {
    mouthTimer += deltaTime;
    moveTimer += deltaTime;

    if (mouthTimer >= 0.13f) {
        mouthOpen = !mouthOpen;
        updateShape();
        mouthTimer = 0.0f;
    }

    if (moveTimer >= 0.35f) {
        moveTimer = 0.0f;
        sf::Vector2f movement = direction * speed;
        shape.move(movement);

        // Проверка на столкновение со стенами
        bool collided = false;
        for (const auto& wall : walls) {
            if (shape.getGlobalBounds().intersects(wall.getGlobalBounds())) {
                collided = true;
                break;
            }
        }

        if (collided) {
            shape.move(-movement);
        }
    }
}

void PacMan::render(sf::RenderWindow& window) {
    shape.setRotation(rotationAngle);
    window.draw(shape);
}

sf::Vector2f PacMan::getPosition() const {
    return shape.getPosition();
}

void PacMan::updateShape() {
    if (mouthOpen) {
        shape.setPointCount(22);
        shape.setPoint(0, sf::Vector2f(Constants::PACMAN_SIZE / 2.0f, Constants::PACMAN_SIZE / 2.0f));
        for (int i = 0; i < 21; ++i) {
            float angle = (i * 15.0f - 150.0f) * 3.14f / 180.0f;
            shape.setPoint(i + 1, sf::Vector2f(Constants::PACMAN_SIZE / 2.0f + (Constants::PACMAN_SIZE / 2.0f) * std::cos(angle), Constants::PACMAN_SIZE / 2.0f + (Constants::PACMAN_SIZE / 2.0f) * std::sin(angle)));
        }
    } else {
        shape.setPointCount(30);
        for (int i = 0; i < 30; ++i) {
            float angle = i * 12 * 3.14f / 180;
            shape.setPoint(i, sf::Vector2f(Constants::PACMAN_SIZE / 2.0f + (Constants::PACMAN_SIZE / 2.0f) * std::cos(angle), Constants::PACMAN_SIZE / 2.0f + (Constants::PACMAN_SIZE / 2.0f) * std::sin(angle)));
        }
    }
}

bool PacMan::checkCollision(const sf::CircleShape& ghostShape) const {
    return shape.getGlobalBounds().intersects(ghostShape.getGlobalBounds());
}