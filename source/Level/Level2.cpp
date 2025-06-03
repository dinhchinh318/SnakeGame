#include "Level2.h"

Level2::Level2() {
    // Bỏ obstacles cũ, xây lại tường bao khung hình
    obstacles.clear();

    // Vị trí cổng
    startPort = {0,1};
    outPort = {cols - 1, rows - 2};

    int midX = cols / 2;
    int midY = rows / 2;
    int offset = 5;    // khoảng cách từ tâm ra góc mỗi nhánh
    int size = 4;      // độ dài mỗi nhánh góc vuông (có thể chỉnh)

    for (int i = 0; i < size; ++i) {
        // Nhánh ngang (trái sang phải)
        obstacles.push_back(sf::Vector2i(midX - offset - i, midY - offset));
        // Nhánh dọc (trên xuống dưới)
        obstacles.push_back(sf::Vector2i(midX - offset, midY - offset - i));
    }

    for (int i = 0; i < size; ++i) {
        // Nhánh ngang (phải sang trái)
        obstacles.push_back(sf::Vector2i(midX + offset + i, midY - offset));
        // Nhánh dọc (trên xuống dưới)
        obstacles.push_back(sf::Vector2i(midX + offset, midY - offset - i));
    }

    for (int i = 0; i < size; ++i) {
        // Nhánh ngang (trái sang phải)
        obstacles.push_back(sf::Vector2i(midX - offset - i, midY + offset));
        // Nhánh dọc (dưới lên trên)
        obstacles.push_back(sf::Vector2i(midX - offset, midY + offset + i));
    }

    for (int i = 0; i < size; ++i) {
        // Nhánh ngang (phải sang trái)
        obstacles.push_back(sf::Vector2i(midX + offset + i, midY + offset));
        // Nhánh dọc (dưới lên trên)
        obstacles.push_back(sf::Vector2i(midX + offset, midY + offset + i));
    }

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

numberLevel Level2::getLevelNumber() const { 
    return numberLevel::L2; 
}

int Level2::getFoodGoal() const { 
    return 1; 
}

const std::vector<sf::Vector2i>& Level2::getObstacles() const { 
    return obstacles; 
}

void Level2::draw(sf::RenderWindow& window, int tileSize)
{
    drawPort(window, tileSize);
    drawObstacles(window, tileSize);
    // ...vẽ các thành phần khác nếu muốn
}


void Level2::drawPort(sf::RenderWindow& window, int tileSize){
    sf::RectangleShape obsShape(sf::Vector2f(tileSize, tileSize));
    obsShape.setFillColor(sf::Color::Green);
    obsShape.setPosition(startPort.x * tileSize, startPort.y * tileSize);
    window.draw(obsShape);
    obsShape.setPosition(outPort.x * tileSize, outPort.y * tileSize);
    window.draw(obsShape);
}

void Level2::addObstacle(sf::Vector2i obstacle){
    obstacles.push_back(obstacle);
}

void Level2::deleteObstacle(sf::Vector2i obstacle){
    obstacles.erase(std::remove(obstacles.begin(), obstacles.end(), obstacle), obstacles.end());
}

