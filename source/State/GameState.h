#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "WindowState.h"

class GameState : public WindowState{
private:
    // Object snake and food
    Snake snake;
    Food food;
    // Level
    std::unique_ptr<Level> currentLevel;
    int foodEaten = 0;
    bool drawFood = true;

    // Textures and Sprites
    sf::Texture yardTexture;
    sf::Sprite yardSprite;

    bool showGameOverPopup = false;
    bool showWinPopup = false;

public:
    void spawnFood();
    void drawYard(sf::RenderWindow& window, int tileSize, int rows, int cols);

    void run();
    void resetGame();
    void start();

    // Level logic
    void setLevel(numberLevel num);
    const Level& getCurrentLevel() const;

    // update model
    void updateGameLogic();
    void checkGameOver();
    void checkLevelComplete();

    // Getters
    int getFoodEaten() const { return foodEaten; }
    bool isDrawFood() const { return drawFood; }
    bool isShowGameOverPopup() const { return showGameOverPopup; }
    bool isShowWinPopup() const { return showWinPopup; }
};

#endif