#include "Food.h"
#include <iostream>

void Food::spawn(const std::vector<sf::Vector2i>& obstacles, const std::vector<sf::Vector2i>& snakeBody, int cols, int rows)
{
    while (true) {
        int x = std::rand() % cols;
        int y = std::rand() % rows;
        sf::Vector2i candidate(x, y);

        // Kiểm tra trùng obstacles
        if (std::find(obstacles.begin(), obstacles.end(), candidate) != obstacles.end())
            continue;
        // Kiểm tra trùng với thân rắn
        if (std::find(snakeBody.begin(), snakeBody.end(), candidate) != snakeBody.end())
            continue;

        // Không trùng, sinh food ở đây
        position = sf::Vector2i(x, y);
        break;
    }
}

void Food::setPosition(sf::Vector2i newPos)
{
    position = newPos;
}


sf::Vector2i Food::getPosition() const 
{
    return position;
}

void Food::draw(sf::RenderWindow& window, int tileSize) 
{
    // Tính vị trí pixel giữa ô lưới
    float pixelX = position.x * tileSize + tileSize / 2.f;
    float pixelY = position.y * tileSize + tileSize / 2.f;

    // Căn giữa sprite trong ô lưới
    foodSprite.setPosition(pixelX, pixelY);

    // Tính scale cho sprite vừa khít 1 ô (nếu cần)
    sf::Vector2u texSize = foodTexture.getSize();
    float scaleX = tileSize / static_cast<float>(texSize.x);
    float scaleY = tileSize / static_cast<float>(texSize.y);
    foodSprite.setScale(scaleX, scaleY);

    window.draw(foodSprite);
}


Food::Food() 
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for random number generation
    // load snake image
    foodTexture.loadFromFile("assets/picture/food.png");

    foodSprite.setTexture(foodTexture);
    //

    foodSprite.setOrigin(foodTexture.getSize().x / 2.f, foodTexture.getSize().y / 2.f);
    //
}

