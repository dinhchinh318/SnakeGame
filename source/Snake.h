#ifndef SNAKE_H_
#define SNAKE_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include "Direction.h"

class Snake{
private:
    std::vector<sf::Vector2i> snake;
    Direction direction;
    bool growNext;
    bool isAlive;
    const int initLength = 4;
    sf::Texture headTexture, bodyTexture, tailTexture, turnTexture;
    sf::Sprite headSprite, bodySprite, tailSprite, turnSprite;
public:
    Snake(sf::Vector2i starPos, Direction dir = RIGHT);
    void setDirection(Direction dir);
    Direction getDirection();
    std::vector<sf::Vector2i> getSnake();
    sf::Vector2i getHeadPosition();
    sf::Vector2i getTailPosition();
    std::vector<sf::Vector2i> getBody();
    bool getIsAlive();
    void setIsAlive(bool isAlive);
    void move();
    void grow();
    bool checkSelfCollision();
    void draw(sf::RenderWindow& window, int tileSize);
    void reset(sf::Vector2i newStart,  Direction dir = RIGHT);
};

#endif