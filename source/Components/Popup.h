#ifndef _POPUP_H_
#define _POPUP_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Button.h"

class Popup
{
public:
    sf::RectangleShape frame;
    sf::Texture background;
    sf::Text title;
    sf::Text content;
    sf::Font font;
    std::vector<Button> choices;

public:
    Popup();
    Popup(sf::Vector2f size, sf::Vector2f pos, int nOfButton);
    void initChoices();
    void setFrameSize(sf::Vector2f);
    void setTextSize(int size);
    void setTitle(std::string title);
    void setContent(std::string content);
    void setFont(sf::Font &font);
    void setFont(std::string filePath);
    void setTextColor(sf::Color color);
    void setBackground(sf::Texture &bgTexture);
    void setBackground(std::string filePath);
    void setBackgroundColor(sf::Color color);
    void setChoiceString(std::string name, int index);
    void setOriginCenterText();
    void setChoiceButtonSize(int width, int height);
    void setNumberOfChoice(int num);
    void drawTo(sf::RenderWindow &window);
    void setPosition(float x, float y);
    sf::Vector2f getSizeFrame();

    void update(sf::Vector2f mousePos) {
        for (auto &choice : choices) {
            choice.update(mousePos);
        }
    }
};

#endif
