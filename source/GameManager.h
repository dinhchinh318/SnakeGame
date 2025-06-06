#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

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

    // Textures and Sprites
    sf::Texture yardTexture;
    sf::Sprite yardSprite;
public:
    // Graphics
    ~GameManager();
    void initWindow();
    sf::RenderWindow &getRenderWindow();
    bool isWindowOpen();

    // Window process
    void clearScreen();
    void pollEvents();
    void update();
    void draw();

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