#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "Snake.h"
#include "Food.h"
#include "Level/LevelFactory.h"
#include <iostream>
#include "Components/Popup.h"
#include "State/WindowState.h"
#include "State/MenuState.h"
#include "State/SettingState.h"
#include "State/GameState.h"

class GameManager {
private:
    const int windowWidth = 800;
    const int windowHeight = 600;
    const int tileSize = 20;
    const int cols = windowWidth / tileSize;
    const int rows = windowHeight / tileSize;

    // Video mode
    sf::RenderWindow window;

    //State
    WindowState *currentState;
    MenuState *menu;
    SettingState *setting;
    GameState *game;

    Snake snake;
    Food food;
    std::unique_ptr<Level> currentLevel;

    int foodEaten = 0;
    bool drawFood = true;

    //Popups
    Popup gameOverPopup;
    Popup winPopup;
    bool showGameOverPopup = false;
    bool showWinPopup = false;

    // Textures and Sprites
    sf::Texture yardTexture;
    sf::Sprite yardSprite;
public:
    //signs to be used in states
    bool hasGameInProgress;
    
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

    //State
    void initMenuState();
    void initSettingState();
    void initGameState();
    void setState(WindowState *state);
    MenuState *getMenuState();
    SettingState *getSettingState();
    GameState *getGameState();
    WindowState *getCurrentState();
    void drawCurrentState();
};

#endif