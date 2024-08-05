#ifndef GHOST_HPP
#define GHOST_HPP

#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Ghost : public Entity {
public:
    Ghost(float x, float y);
    void update(float deltaTime, const std::vector<sf::RectangleShape>& walls) override;
    void update(float deltaTime, const sf::Vector2f& targetPosition, const std::vector<sf::RectangleShape>& walls);
    void render(sf::RenderWindow& window) override;
    sf::Vector2f getPosition() const override; // Переопределение метода
    const sf::CircleShape& getShape() const { return shape; } // Добавленный метод

private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    int steps;
    void changeDirection();
    sf::Vector2f findNearestCell(const sf::Vector2f& targetPosition);
};

#endif // GHOST_HPP