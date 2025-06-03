#include "Level.h"

sf::Vector2i Level::getStartPort(){
    return startPort;
}

sf::Vector2i Level::getOutPort(){
    return outPort;
}

void Level::drawObstacles(sf::RenderWindow& window, int tileSize)
    {
        // load snake image
        wallTexture.loadFromFile("assets/picture/wall.jpg");

        wallSprite.setTexture(wallTexture);
        //

        wallSprite.setOrigin(wallTexture.getSize().x / 2.f, wallTexture.getSize().y / 2.f);
        //

        for (const auto& pos : obstacles) {
            // obsShape.setPosition(pos.x * tileSize, pos.y * tileSize);
            // window.draw(obsShape);
            // Tính vị trí pixel giữa ô lưới
            float pixelX = pos.x * tileSize + tileSize / 2.f;
            float pixelY = pos.y * tileSize + tileSize / 2.f;

            // Căn giữa sprite trong ô lưới
            wallSprite.setPosition(pixelX, pixelY);

            // Tính scale cho sprite vừa khít 1 ô (nếu cần)
            sf::Vector2u texSize = wallTexture.getSize();
            float scaleX = tileSize / static_cast<float>(texSize.x);
            float scaleY = tileSize / static_cast<float>(texSize.y);
            wallSprite.setScale(scaleX, scaleY);

            window.draw(wallSprite);
        }
    }