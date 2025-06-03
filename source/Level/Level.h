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
    std::vector<sf::Vector2i> obstacles;

    sf::Texture wallTexture;
    sf::Sprite wallSprite;

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
    virtual void addObstacle(sf::Vector2i obstacle) = 0;
    virtual void deleteObstacle(sf::Vector2i obstacle) = 0;
    virtual void draw(sf::RenderWindow& window, int tileSize) = 0;
    void drawObstacles(sf::RenderWindow& window, int tileSize);
};


#endif