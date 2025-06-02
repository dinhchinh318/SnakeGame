#include "Snake.h"
#include <iostream>
Snake::Snake(sf::Vector2i starPos, Direction dir){
    direction = dir;
    speed = 0.5f;
    growNext = false;

    // load snake image
    headTexture.loadFromFile("assets/picture/snake_head.png");
    bodyTexture.loadFromFile("assets/picture/snake_body.png");
    tailTexture.loadFromFile("assets/picture/snake_tail.png");
    turnTexture.loadFromFile("assets/picture/snake_turn.png");

    headSprite.setTexture(headTexture);
    bodySprite.setTexture(bodyTexture);
    tailSprite.setTexture(tailTexture);
    turnSprite.setTexture(turnTexture);
    //

    headSprite.setOrigin(headTexture.getSize().x / 2.f, headTexture.getSize().y / 2.f);
    bodySprite.setOrigin(bodyTexture.getSize().x / 2.f, bodyTexture.getSize().y / 2.f);
    tailSprite.setOrigin(tailTexture.getSize().x / 2.f, tailTexture.getSize().y / 2.f);
    turnSprite.setOrigin(turnTexture.getSize().x / 2.f, turnTexture.getSize().y / 2.f);
    //
    
    sf::Vector2i delta(0.f, 0.f);
    switch (dir) {
        case UP:
            delta = sf::Vector2i(0.f, 1.f);
            break;
        case DOWN:
            delta = sf::Vector2i(0.f, -1.f);
            break;
        case LEFT: 
            delta = sf::Vector2i(1.f, 0.f); 
            break;
        case RIGHT:
            delta = sf::Vector2i(-1.f, 0.f); 
            break;
        default: 
            break;
    }

    for (int i = 0; i < initLength; ++i) {
        snake.push_back(starPos + delta * static_cast<int>(i));
    }
}

void Snake::setDirection(Direction dir){
    if (isOpposite(direction, dir)) return;
    direction = dir;
}

Direction Snake::getDirection(){
    return direction;
}

std::vector<sf::Vector2i> Snake::getSnake() {
    return snake;
}

sf::Vector2i Snake::getHeadPosition() {
    if (snake.empty()) return sf::Vector2i(-1.f, -1.f);
    return snake.front();
}

sf::Vector2i Snake::getTailPosition() {
    if (snake.empty()) return sf::Vector2i(-1.f, -1.f);
    return snake.back();
}

std::vector<sf::Vector2i> Snake::getBody() {
    int n = snake.size();
    std::vector<sf::Vector2i> body;
    for (int i = 0; i < n; i++){
        if (i == 0 || i == n - 1){
            continue;
        }
        body.push_back(snake[i]);
    }
    return body;
}

void Snake::move(){
    sf::Vector2i newHead = this->getHeadPosition();

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
    sf::Vector2i newHead = this->getHeadPosition();

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

    for (int i = 1; i < snake.size(); ++i) {
        if (newHead == snake[i]) {
            return true;
        }
    }

    return false;
}

void Snake::reset(sf::Vector2i newStart,  Direction dir){
    direction = dir;
    growNext = false;
    snake.clear();

    sf::Vector2i delta(0.f, 0.f);
    switch (dir) {
        case UP:
            delta = sf::Vector2i(0.f, 1.f);
            break;
        case DOWN:
            delta = sf::Vector2i(0.f, -1.f);
            break;
        case LEFT: 
            delta = sf::Vector2i(1.f, 0.f); 
            break;
        case RIGHT:
            delta = sf::Vector2i(-1.f, 0.f); 
            break;
        default: 
            break;
    }

    for (int i = 0; i < initLength; ++i) {
        snake.push_back(newStart + delta * static_cast<int>(i));
    }
}

void Snake::draw(sf::RenderWindow& window, int tileSize){
    int length = snake.size();
    for (int i = 0; i < length; i++){
        sf::Sprite *sprite;

        if (i == 0) {
            sprite = &headSprite;
        } else if (i == length - 1) {
            sprite = &tailSprite;
        } else {
            sprite = &bodySprite;
            sf::Vector2i prev = snake[i - 1];
            sf::Vector2i curr = snake[i];
            sf::Vector2i next = snake[i + 1];

            sf::Vector2i dir1 = prev - curr;
            sf::Vector2i dir2 = next - curr;

            if (dir1.x != dir2.x && dir1.y != dir2.y) {
                sprite = &turnSprite;
            }
        }

        float scaleX = tileSize / static_cast<float>(sprite->getTexture()->getSize().x);
        float scaleY = tileSize / static_cast<float>(sprite->getTexture()->getSize().y);
        sprite->setScale(scaleX, scaleY);

        sprite->setPosition((snake[i].x + 0.5f) * tileSize, (snake[i].y + 0.5f) * tileSize);

        if (i == 0) {
            switch (direction) {
                case UP:
                    sprite->setRotation(180); 
                    break;
                case RIGHT: 
                    sprite->setRotation(270);
                    break;
                case DOWN:
                    sprite->setRotation(0);
                    break;
                case LEFT:
                    sprite->setRotation(90);
                    break;
            }
        }
        else if (i == length - 1) {
            sf::Vector2i tail = snake[i];
            sf::Vector2i prev = snake[i - 1];
            sf::Vector2i diff = tail - prev;

            if (diff.x == 1) {
                sprite->setRotation(270);
            } else if (diff.x == -1) {
                sprite->setRotation(90);
            } else if (diff.y == 1) {
                sprite->setRotation(0);
            } else if (diff.y == -1) {
                sprite->setRotation(180);
            }
        }
        else if (sprite == &turnSprite) {
            sf::Vector2i prev = snake[i - 1];
            sf::Vector2i curr = snake[i];
            sf::Vector2i next = snake[i + 1];
            sf::Vector2i dir1 = prev - curr;
            sf::Vector2i dir2 = next - curr;

            if ((dir1.x == 1 && dir2.y == 1) || (dir2.x == 1 && dir1.y == 1)) {
                sprite->setRotation(270);
            } else if ((dir1.x == -1 && dir2.y == 1) || (dir2.x == -1 && dir1.y == 1)) {
                sprite->setRotation(0);
            } else if ((dir1.x == 1 && dir2.y == -1) || (dir2.x == 1 && dir1.y == -1)) {
                sprite->setRotation(180);
            } else if ((dir1.x == -1 && dir2.y == -1) || (dir2.x == -1 && dir1.y == -1)) {
                sprite->setRotation(90);
            }
        }
        else {
            sf::Vector2i prev = snake[i - 1];
            sf::Vector2i next = snake[i + 1];

            if (prev.x == next.x) {
                sprite->setRotation(0);
            } else if (prev.y == next.y) {
                sprite->setRotation(90);
            }
        }

        window.draw(*sprite);
    }
}
