#ifndef WORLDOBJECTS_HPP
#define WORLDOBJECTS_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class WorldObjects {
public:
    WorldObjects(float cellSize, const std::vector<sf::RectangleShape>& walls);
    void update(const sf::Vector2f& pacmanPosition, int& score);
    void render(sf::RenderWindow& window);

private:
    std::vector<sf::CircleShape> points;
    float cellSize;
    const std::vector<sf::RectangleShape>& walls;

    bool isPositionValid(const sf::Vector2f& position, float radius) const;
};

#endif // WORLDOBJECTS_HPP