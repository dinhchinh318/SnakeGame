#ifndef _LEVEL2_H_
#define _LEVEL2_H_

#include "Level.h"

class Level2 : public Level {
    std::vector<sf::Vector2i> obstacles;
public:
    Level2();
    numberLevel getLevelNumber() const override;
    int getFoodGoal() const override;
    const std::vector<sf::Vector2i>& getObstacles() const override;

    void draw(sf::RenderWindow& window, int tileSize) override;
    void drawObstacles(sf::RenderWindow& window, int tileSize) override;
    // void update(sf::RenderWindow& window, Snake& snake, GameManager& gm) override;
    // void pollEvents(GameManager& gm) override;
};

#endif