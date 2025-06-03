#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include "WindowState.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MenuState : public WindowState { 
private:
    sf::RectangleShape background;
    sf::Texture bg_texture;
    sf::Font font;
    sf::Text gameTitle;
    int currentChoice;
    int numberOfButtons;
    Button button[5];

    // add sound effect
    sf::SoundBuffer soundBuffer;
    sf::Sound selectionSound;

public:
    void pollEvents(GameManager *gameMan);
    void update(GameManager *gameMan);
    void draw(GameManager *gameMan);
    void init(GameManager *gameMan);

    MenuState();
};

#endif