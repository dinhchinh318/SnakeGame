#include "Food.h"
#include <iostream>

void Food::spawn() 
{
    int x = std::rand() % 40;
    int y = std::rand() % 30;
    position = sf::Vector2f(x, y);
    std::cout << "Food at: " << position.x << ", " << position.y << std::endl;
}

sf::Vector2f Food::getPosition() const 
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

