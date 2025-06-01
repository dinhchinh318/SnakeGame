#include "Snake.h"

Snake::Snake(sf::Vector2f starPos, Direction dir){
    direction = dir;
    speed = 0.5f;
    growNext = false;
    
    sf::Vector2f delta(0.f, 0.f);
    switch (dir) {
        case UP:
            delta = sf::Vector2f(0.f, 1.f);
            break;
        case DOWN:
            delta = sf::Vector2f(0.f, -1.f);
            break;
        case LEFT: 
            delta = sf::Vector2f(1.f, 0.f); 
            break;
        case RIGHT:
            delta = sf::Vector2f(-1.f, 0.f); 
            break;
        default: 
            break;
    }

    for (int i = 0; i < initLength; ++i) {
        snake.push_back(starPos + delta * static_cast<float>(i));
    }
}

void Snake::setDirection(Direction dir){
    if (isOpposite(direction, dir)) return;
    direction = dir;
}

Direction Snake::getDirection(){
    return direction;
}

sf::Vector2f Snake::getHeadPosition(){
    if (snake.empty()) return sf::Vector2f(-1.f, -1.f);
    return snake.front();
}

sf::Vector2f Snake::getTailPosition(){
    if (snake.empty()) return sf::Vector2f(-1.f, -1.f);
    return snake.back();
}

std::vector<sf::Vector2f> Snake::getBody(){
    int n = snake.size();
    std::vector<sf::Vector2f> body;
    for (int i = 0; i < n; i++){
        if (i == 0 || i == n - 1){
            continue;
        }
        body.push_back(snake[i]);
    }
    return body;
}

void Snake::move(){
    sf::Vector2f newHead = this->getHeadPosition();

    switch(direction){
        case UP:
            newHead.y -= 1;
            break;
        case DOWN:
            newHead.y += 1;
            break;
        case LEFT:
            newHead.x -= 1;
            break;
        case RIGHT:
            newHead.x += 1;
            break;
        default:
            break;
    }

    snake.insert(snake.begin(), newHead);

    if (growNext == false){
        snake.pop_back();
    } else{
        growNext = false;
    }
}

void Snake::grow(){
    growNext = true;
}

bool Snake::checkSelfCollision(){
    sf::Vector2f newHead = this->getHeadPosition();

    switch(direction){
        case UP:
            newHead.y -= 1;
            break;
        case DOWN:
            newHead.y += 1;
            break;
        case LEFT:
            newHead.x -= 1;
            break;
        case RIGHT:
            newHead.x += 1;
            break;
        default:
            break;
    }

    for (auto x : snake){
        if (newHead == x){
            return true;
        }
    }

    return false;
}

void Snake::reset(sf::Vector2f newStart,  Direction dir){
    direction = dir;
    growNext = false;
    snake.clear();

    sf::Vector2f delta(0.f, 0.f);
    switch (dir) {
        case UP:
            delta = sf::Vector2f(0.f, 1.f);
            break;
        case DOWN:
            delta = sf::Vector2f(0.f, -1.f);
            break;
        case LEFT: 
            delta = sf::Vector2f(1.f, 0.f); 
            break;
        case RIGHT:
            delta = sf::Vector2f(-1.f, 0.f); 
            break;
        default: 
            break;
    }

    for (int i = 0; i < initLength; ++i) {
        snake.push_back(newStart + delta * static_cast<float>(i));
    }
}

void Snake::draw(sf::RenderWindow& window, int tileSize, const sf::Color color){
    sf::RectangleShape segment(sf::Vector2f(tileSize, tileSize));
    segment.setFillColor(color);

    int length = snake.size();

    for (int i = 0; i < length; i++){
        segment.setPosition(snake[i].x * tileSize, snake[i].y * tileSize);

        if (i == 0) {
            segment.setFillColor(sf::Color::Yellow);
        } else if (i == length - 1) {
            segment.setFillColor(sf::Color::Red);
        } else {
            segment.setFillColor(sf::Color::Green);
        }

        window.draw(segment);
    }
}
