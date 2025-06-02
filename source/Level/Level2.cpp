#include "Level2.h"

Level2::Level2() {
    // Bỏ obstacles cũ, xây lại tường bao khung hình
    obstacles.clear();
    // Cạnh trên và dưới
    for (int x = 0; x < cols; ++x) {
        obstacles.push_back({x, 0});           // Trên
        obstacles.push_back({x, rows - 1});    // Dưới
    }
    // Cạnh trái và phải
    for (int y = 1; y < rows - 1; ++y) { // Không lặp lại 4 góc
        obstacles.push_back({0, y});           // Trái
        obstacles.push_back({cols - 1, y});    // Phải
    }

    startPort = {10, 1};
}

numberLevel Level2::getLevelNumber() const { 
    return numberLevel::L2; 
}

int Level2::getFoodGoal() const { 
    return 10; 
}

const std::vector<sf::Vector2i>& Level2::getObstacles() const { 
    return obstacles; 
}

void Level2::draw(sf::RenderWindow& window, int tileSize)
{
    drawObstacles(window, tileSize);
    // ...vẽ các thành phần khác nếu muốn
}

void Level2::drawObstacles(sf::RenderWindow& window, int tileSize)
{
    sf::RectangleShape obsShape(sf::Vector2f(tileSize, tileSize));
    obsShape.setFillColor(sf::Color::Red); // màu tường, bạn có thể chỉnh
    for (const auto& pos : obstacles) {
        obsShape.setPosition(pos.x * tileSize, pos.y * tileSize);
        window.draw(obsShape);
    }
}

// void Level2::update(sf::RenderWindow& window, Snake& snake, GameManager& gm)
// {

// }

// void Level2::pollEvents(GameManager& gm)
// {

// }

