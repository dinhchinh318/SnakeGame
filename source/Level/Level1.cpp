#include "Level1.h"

Level1::Level1() {
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

    startPort = {1,1};
}

numberLevel Level1::getLevelNumber() const { 
    return numberLevel::L1; 
}

int Level1::getFoodGoal() const { 
    return 5;
}

const std::vector<sf::Vector2i>& Level1::getObstacles() const {
    return obstacles; 
}

void Level1::draw(sf::RenderWindow& window, int tileSize)
{
    drawObstacles(window, tileSize);
    // ...vẽ các thành phần khác nếu muốn
}

void Level1::drawObstacles(sf::RenderWindow& window, int tileSize)
{
    sf::RectangleShape obsShape(sf::Vector2f(tileSize, tileSize));
    obsShape.setFillColor(sf::Color::Red); // màu tường, bạn có thể chỉnh
    for (const auto& pos : obstacles) {
        obsShape.setPosition(pos.x * tileSize, pos.y * tileSize);
        window.draw(obsShape);
    }
}

// 3 hàm sau để trống hoặc viết logic riêng cho từng level
// void Level1::update(sf::RenderWindow& window, Snake& snake, GameManager& gm) {}
// void Level1::pollEvents(GameManager& gm) {}
