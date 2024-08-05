#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity(float x, float y, float speed);
    virtual void update(float deltaTime, const std::vector<sf::RectangleShape>& walls) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual sf::Vector2f getPosition() const = 0; // Чисто виртуальный метод

protected:
    float speed;
    float moveTimer;
};

#endif // ENTITY_HPP