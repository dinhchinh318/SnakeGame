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

    // Textures and Sprites
    sf::Texture yardTexture;
    sf::Sprite yardSprite;

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

    void drawYard(sf::RenderWindow& window, int tileSize, int rows, int cols);

    bool isWindowOpen();
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
    void updatePopups();

    // Popups
    void showGameOverPopupFunc();
    void showWinPopupFunc();

    void initializePopups  (
                                Popup& p,
                                int popupWidth, int popupHeight, 
                                const std::string& title,
                                const std::string& content,
                                const std::vector<std::string>& ch,
                                sf::Font& font,
                                int buttonWidth, int buttonHeight
                            );

    // Getters
    int getFoodEaten() const { return foodEaten; }
    bool isDrawFood() const { return drawFood; }
    bool isShowGameOverPopup() const { return showGameOverPopup; }
    bool isShowWinPopup() const { return showWinPopup; }
};

#endif