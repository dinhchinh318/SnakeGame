#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "WindowState.h"
#include "Snake.h"
#include "Food.h"
#include "Components/Popup.h"
#include "Level/LevelFactory.h"

class GameState : public WindowState{
private:
    const int windowWidth = 800;
    const int windowHeight = 600;
    const int tileSize = 20;
    const int cols = windowWidth / tileSize;
    const int rows = windowHeight / tileSize;
    // Object snake and food
    Snake* snake;
    Food* food;
    // Level
    std::unique_ptr<Level> currentLevel;
    int foodEaten;
    bool drawFood;

    sf::Font font;
    
    // Textures and Sprites
    sf::Texture yardTexture;
    sf::Sprite yardSprite;

    bool showGameOverPopup = false;
    bool showWinPopup = false;

    Popup gameOverPopup;
    Popup winPopup;

public:
    ~GameState();
    void init(GameManager *gameMan);
    void pollEvents(GameManager *gameMan);
    void update(GameManager *gameMan);
    void draw(GameManager *gameMan);
    
    void spawnFood();
    void drawYard(sf::RenderWindow& window, int tileSize, int rows, int cols);

    void resetGame();
    void start(GameManager *gameMan);
    void run(GameManager *gameMan);

//     // Level logic
    void setLevel(numberLevel num);
    const Level& getCurrentLevel() const;

//     // update model
    void updateGameLogic();
    void checkGameOver();
    void checkLevelComplete();

    void initializePopups  (
                                Popup& p,
                                int popupWidth, int popupHeight, 
                                const std::string& title,
                                const std::string& content,
                                const std::vector<std::string>& ch,
                                sf::Font& font,
                                int buttonWidth, int buttonHeight
                            );
    void updatePopups(GameManager* gameMan);

//     // Getters
//     int getFoodEaten() const { return foodEaten; }
//     bool isDrawFood() const { return drawFood; }
//     bool isShowGameOverPopup() const { return showGameOverPopup; }
//     bool isShowWinPopup() const { return showWinPopup; }
};

#endif