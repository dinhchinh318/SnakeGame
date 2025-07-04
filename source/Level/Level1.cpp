#include "Level1.h"

Level1::Level1() {
    // Bỏ obstacles cũ, xây lại tường bao khung hình
    obstacles.clear();
    // Vị trí cổng
    startPort = {0,1};
    outPort = {cols - 1, rows - 2};

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

    obstacles.erase(std::remove(obstacles.begin(), obstacles.end(), startPort), obstacles.end());
}

numberLevel Level1::getLevelNumber() const { 
    return numberLevel::L1; 
}

int Level1::getFoodGoal() const { 
    return 1;
}

const std::vector<sf::Vector2i>& Level1::getObstacles() const {
    return obstacles; 
}

void Level1::draw(sf::RenderWindow& window, int tileSize)
{
    drawPort(window, tileSize);
    drawObstacles(window, tileSize);
    // ...vẽ các thành phần khác nếu muốn
}

void Level1::drawPort(sf::RenderWindow& window, int tileSize){
    sf::RectangleShape obsShape(sf::Vector2f(tileSize, tileSize));
    obsShape.setFillColor(sf::Color::Green);
    obsShape.setPosition(startPort.x * tileSize, startPort.y * tileSize);
    window.draw(obsShape);
    obsShape.setPosition(outPort.x * tileSize, outPort.y * tileSize);
    window.draw(obsShape);
}

void Level1::addObstacle(sf::Vector2i obstacle){
    if (std::find(obstacles.begin(), obstacles.end(), obstacle) == obstacles.end()){
        obstacles.push_back(obstacle);
    }
}

void Level1::deleteObstacle(sf::Vector2i obstacle){
    obstacles.erase(std::remove(obstacles.begin(), obstacles.end(), obstacle), obstacles.end());
}
