#ifndef _LEVEL3_H_
#define _LEVEL3_H_

#include "Level.h"

class Level1 : public Level {
    
public:
    Level1();
    numberLevel getLevelNumber() const override;
    int getFoodGoal() const override;
    const std::vector<sf::Vector2i>& getObstacles() const override;
    void addObstacle(sf::Vector2i obstacle) override;
    void deleteObstacle(sf::Vector2i obstacle) override;
    void draw(sf::RenderWindow& window, int tileSize) override;
    void drawPort(sf::RenderWindow& window, int tileSize);
};

#endif