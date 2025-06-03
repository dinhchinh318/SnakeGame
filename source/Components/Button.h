#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <iostream>
#include <SFML/Graphics.hpp>

struct UITheme {
    sf::Color background = sf::Color(24, 26, 27);
    sf::Color buttonColor = sf::Color(44, 62, 90);
    sf::Color hoverColor = sf::Color(52, 152, 219);
    sf::Color textColor = sf::Color(236, 240, 241);
    sf::Color textColor1 = sf::Color(231, 76, 60);
    sf::Color borderColor = sf::Color(41, 128, 185);
    float borderRadius = 12.f;
    int outlineThickness = 3;
    unsigned int characterSize = 22;
};

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    UITheme theme;
    sf::Color currentColor;

public:
    Button();
    Button(const std::string& label, sf::Vector2f pos, sf::Vector2f size, sf::Font& f, UITheme theme);

    void setFont(sf::Font &font);
    void setTextSize(unsigned int size);
    void setTextColor(sf::Color color);
    void setTitle(std::string str);
    void setBackgroundColor(sf::Color color);
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setScale(float w, float h);
    void setTexture(sf::Texture &texture);
    int getLocalBoundsWidth();
    int getLocalBoundsHeight();
    int getPositionX();
    int getPositionY();
    int getSizeWidth();
    int getSizeHeight();
    void drawTo(sf::RenderWindow &window);

    void centerText();

    void draw(sf::RenderWindow& window);

    void update(sf::Vector2f mousePos);

    bool isClicked(sf::Vector2f mousePos);

    std::string getLabel() const;

    void setButtonColor(sf::Color color);
    
    bool isMouseOver(sf::RenderWindow &window);
    void setOriginToCenter();
    void setOriginToCenterForText();
};

#endif
