#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <SFML/Graphics.hpp>
#include "vector"

enum class numberLevel {
    L1,
    L2,
    L3,
    L4,
};

class Level {
protected:
    const int windowWidth = 800;
    const int windowHeight = 600;
    const int tileSize = 20;
    const int cols = windowWidth / tileSize;
    const int rows = windowHeight / tileSize;
    sf::Vector2i startPort;
    sf::Vector2i outPort;
public:
    virtual ~Level() = default;
    virtual numberLevel getLevelNumber() const = 0;
    virtual int getFoodGoal() const = 0;
    virtual sf::Vector2i getStartPort();
    virtual sf::Vector2i getOutPort();
    virtual const std::vector<sf::Vector2i>& getObstacles() const = 0;

    virtual void draw(sf::RenderWindow& window, int tileSize) = 0;
    virtual void drawObstacles(sf::RenderWindow& window, int tileSize) = 0;
    // virtual void update(sf::RenderWindow& window, Snake& snake, GameManager& gm) = 0;
    // virtual void pollEvents(GameManager& gm) = 0;
};


#endif