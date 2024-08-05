#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "Entity.hpp"

class PacMan : public Entity {
public:
    PacMan(float x, float y);
    void handleInput();
    void update(float deltaTime, const std::vector<sf::RectangleShape>& walls) override;
    void render(sf::RenderWindow& window) override;
    sf::Vector2f getPosition() const override; // Переопределение метода
    bool checkCollision(const sf::CircleShape& ghostShape) const; // Добавленный метод

private:
    void updateShape();
    sf::Vector2f direction;
    bool mouthOpen;
    float mouthTimer;
    float rotationAngle;
    sf::ConvexShape shape;
};

#endif // PACMAN_HPP