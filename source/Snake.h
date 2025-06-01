#ifndef SNAKE_H_
#define SNAKE_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include "Direction.h"

class Snake{
private:
    std::vector<sf::Vector2f> snake;
    Direction direction;
    float speed;
    bool growNext;
    const int initLength = 4;
    sf::Texture headTexture, bodyTexture, tailTexture, turnTexture;
    sf::Sprite headSprite, bodySprite, tailSprite, turnSprite;
public:
    Snake(sf::Vector2f starPos, Direction dir = RIGHT);
    void setDirection(Direction dir);
    Direction getDirection();
    sf::Vector2f getHeadPosition();
    sf::Vector2f getTailPosition();
    std::vector<sf::Vector2f> getBody();
    void move();
    void grow();
    bool checkSelfCollision();
    void draw(sf::RenderWindow& window, int tileSize);
    void reset(sf::Vector2f newStart,  Direction dir = RIGHT);
};

#endif