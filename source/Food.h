#ifndef _FOOD_H_
#define _FOOD_H_

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

class Food 
{
private:
    sf::Vector2f position;
public:
    Food();

    void spawn();

    sf::Vector2f getPosition() const;

    void draw(sf::RenderWindow& window, int tileSize);
};

#endif