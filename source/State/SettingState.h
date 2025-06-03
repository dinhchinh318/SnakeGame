#ifndef _SETTING_STATE_H_
#define _SETTING_STATE_H_

#include "WindowState.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SettingState : public WindowState { 
private:
    Button behindBar[2];
    Button frontBar[2];

    Button backButton;

    sf::Text bar1Title;
    sf::Text bar2Title;

    sf::Texture bg_texture;
    sf::RectangleShape background;

    sf::Font font;

    int changeMusicVol;
    int changeSoundVol;

public:
    SettingState();
    void init(GameManager *gameMan);
    void pollEvents(GameManager *gameMan);
    void update(GameManager *gameMan);
    void draw(GameManager *gameMan);

    // getter and setter
    int getBarMusicVolume();
    int getBarSoundVolume();
};

#endif