// #ifndef _BUTTON_H_
// #define _BUTTON_H_

// #include <iostream>
// #include <SFML/Graphics.hpp>

// using namespace std;

// struct UITheme {
//     sf::Color background = sf::Color(24, 26, 27);  // Đen xám tinh tế
//     sf::Color buttonColor = sf::Color(44, 62, 90);  // Xanh navy trầm
//     sf::Color hoverColor = sf::Color(52, 152, 219);  // Xanh biển nhạt (hiệu ứng hover)
//     sf::Color textColor = sf::Color(236, 240, 241);  // Trắng xám nhẹ
//     sf::Color textColor1 = sf::Color(231, 76, 60);  // Đỏ san hô (để làm điểm nhấn)
//     sf::Color borderColor = sf::Color(41, 128, 185);  // Xanh dương đậm
//     float borderRadius = 12.f;  // Bo góc nhẹ nhàng
//     int outlineThickness = 3;  // Độ dày viền vừa phải

//     unsigned int characterSize = 22;  // Kích thước chữ rõ nét
// };

// class Button {
// private:
//     sf::RectangleShape shape;
//     sf::Text text;
//     sf::Font font;
//     UITheme theme;
//     sf::Color currentColor;

// public:
//     // Constructor
//     Button();
//     Button(const std::string& label, sf::Vector2f pos, sf::Vector2f size, sf::Font& f, UITheme theme);

//     // function
//     void setFont(sf::Font &font);
//     void setTextSize(unsigned int size);
//     void setTextColor(sf::Color color);
//     void setTitle(std::string str);
//     void setBackgroundColor(sf::Color color);
//     void setPosition(float x, float y);
//     void setSize(float width, float height);
//     void setScale(float w, float h);
//     void setTexture(sf::Texture &texture);
//     int getLocalBoundsWidth();
//     int getLocalBoundsHeight();
//     int getPositionX();
//     int getPositionY();
//     int getSizeWidth();
//     int getSizeHeight();
//     void drawTo(sf::RenderWindow &window);

//     void centerText();

//     void draw(sf::RenderWindow& window) {
//         shape.setFillColor(currentColor);
//         window.draw(shape);
//         window.draw(text);
//     }

//     void update(sf::Vector2f mousePos) {
//         sf::Color targetColor = theme.buttonColor;
//         if (shape.getGlobalBounds().contains(mousePos)) {
//             targetColor = theme.hoverColor;
//         }

//         float factor = 0.1f;
//         currentColor.r += (targetColor.r - currentColor.r) * factor;
//         currentColor.g += (targetColor.g - currentColor.g) * factor;
//         currentColor.b += (targetColor.b - currentColor.b) * factor;
//     }

//     bool isClicked(sf::Vector2f mousePos) {
//         return shape.getGlobalBounds().contains(mousePos);
//     }

//     std::string getLabel() const {
//         return text.getString();
//     }

//     void setButtonColor(sf::Color color) {
//         shape.setFillColor(color);
//     }
    
//     bool isMouseOver(sf::RenderWindow &window);
//     void setOriginToCenter();
//     void setOriginToCenterForText();
// };

// #endif
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
