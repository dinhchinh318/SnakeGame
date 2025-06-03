#ifndef _FOOD_H_
#define _FOOD_H_

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Food 
{
private:
    sf::Vector2i position;
    sf::Texture foodTexture;
    sf::Sprite foodSprite;
public:
    Food();

    void spawn(const std::vector<sf::Vector2i>& obstacles, const std::vector<sf::Vector2i>& snakeBody, int cols, int rows);

    void setPosition(sf::Vector2i newPos);

    sf::Vector2i getPosition() const;

    void draw(sf::RenderWindow& window, int tileSize);
};

#endif