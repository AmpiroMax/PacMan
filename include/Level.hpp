#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Level {
public:
    Level();
    const std::vector<sf::RectangleShape>& getWalls() const;
    sf::Vector2i getPacManSpawn() const;
    std::vector<sf::Vector2i> getGhostSpawns() const;
    void render(sf::RenderWindow& window);

private:
    void createLevel();
    std::vector<sf::RectangleShape> walls;
    sf::Vector2i pacManSpawn;
    std::vector<sf::Vector2i> ghostSpawns;
};

#endif // LEVEL_HPP