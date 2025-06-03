#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "Snake.h"
#include "Food.h"
#include "Level/LevelFactory.h"
#include <iostream>
#include "Components/Popup.h"

class GameManager {
private:
    sf::RenderWindow window;

    Snake snake;
    Food food;
    std::unique_ptr<Level> currentLevel;

    int foodEaten = 0;
    bool drawFood = true;

    Popup gameOverPopup;
    Popup winPopup;
    bool showGameOverPopup = false;
    bool showWinPopup = false;

    const int windowWidth = 800;
    const int windowHeight = 600;
    const int tileSize = 20;
    const int cols = windowWidth / tileSize;
    const int rows = windowHeight / tileSize;

public:
    GameManager() : snake(sf::Vector2i(cols / 2, rows / 2)), food() {}

    // Graphics
    ~GameManager();
    void initWindow();

    void spawnFood();
    sf::RenderWindow &getRenderWindow();

    // Window process
    void clearScreen();
    void pollEvents();
    void update();
    void draw();

    bool isWindowOpen();
    void run();
    void resetGame();
    void start();

    //
    void setLevel(numberLevel num);
    const Level& getCurrentLevel() const;

    void updateGameLogic();

    void checkGameOver();
    void checkLevelComplete();
    void updatePopups();

    // Popups
    void showGameOverPopupFunc();
    void showWinPopupFunc();

    // Getters
    int getFoodEaten() const { return foodEaten; }
    bool isDrawFood() const { return drawFood; }
    bool isShowGameOverPopup() const { return showGameOverPopup; }
    bool isShowWinPopup() const { return showWinPopup; }
};

#endif