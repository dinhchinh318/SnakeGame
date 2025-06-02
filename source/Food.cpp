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


sf::Vector2i Food::getPosition() const 
{
    return position;
}

void Food::draw(sf::RenderWindow& window, int tileSize) 
{
    sf::RectangleShape foodShape(sf::Vector2f(tileSize, tileSize));
    foodShape.setPosition(position.x * tileSize, position.y * tileSize);
    foodShape.setFillColor(sf::Color::Red);
    window.draw(foodShape);
}


Food::Food() 
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for random number generation
    // spawn();
}

