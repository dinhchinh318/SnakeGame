#include "Button.h"

Button::Button() : theme(UITheme()), currentColor(theme.buttonColor) {
    shape.setSize({100, 50});
    shape.setFillColor(currentColor);
    shape.setOutlineColor(theme.borderColor);
    shape.setOutlineThickness(theme.outlineThickness);

    text.setFont(font);
    text.setCharacterSize(theme.characterSize);
    text.setFillColor(theme.textColor);
    centerText();
}

Button::Button(const std::string& label, sf::Vector2f pos, sf::Vector2f size, sf::Font& f, UITheme theme)
    : font(f), theme(theme), currentColor(theme.buttonColor) {

    shape.setPosition(pos);
    shape.setSize(size);
    shape.setFillColor(currentColor);
    shape.setOutlineColor(theme.borderColor);
    shape.setOutlineThickness(theme.outlineThickness);

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(theme.characterSize);
    text.setFillColor(theme.textColor);

    centerText();
}

void Button::setFont(sf::Font &font) {
    text.setFont(font);
    centerText();
}

void Button::setTextSize(unsigned int size) {
    text.setCharacterSize(size);
    centerText();
}

void Button::setTextColor(sf::Color color) {
    text.setFillColor(color);
}

void Button::setTitle(std::string str) {
    text.setString(str);
    centerText();
}

void Button::setBackgroundColor(sf::Color color) {
    shape.setFillColor(color);
}

void Button::setPosition(float x, float y) {
    shape.setPosition(x, y);
    centerText();
}

void Button::setSize(float width, float height) {
    shape.setSize({width, height});
    centerText();
}

void Button::setScale(float w, float h) {
    this->shape.setScale(w, h);
    centerText();
}

void Button::setTexture(sf::Texture& texture) {
    this->shape.setTexture(&texture);
}

int Button::getLocalBoundsWidth() {
    return this->shape.getLocalBounds().width;
}

int Button::getLocalBoundsHeight() {
    return this->shape.getLocalBounds().height;
}

int Button::getPositionX() {
    return this->shape.getPosition().x;
}

int Button::getPositionY() {
    return this->shape.getPosition().y;
}

int Button::getSizeWidth() {
    return this->shape.getSize().x;
}

int Button::getSizeHeight() {
    return this->shape.getSize().y;
}

void Button::setOriginToCenter() {
    this->shape.setOrigin(this->shape.getLocalBounds().width / 2, this->shape.getLocalBounds().height / 2);
}

void Button::setOriginToCenterForText() {
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
}

void Button::centerText() {
    auto bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f,
                   bounds.top + bounds.height / 2.0f);

    sf::Vector2f shapePos = shape.getPosition();
    sf::Vector2f shapeSize = shape.getSize();

    text.setPosition(shapePos.x + shapeSize.x / 2.0f,
                     shapePos.y + shapeSize.y / 2.0f);
}

void Button::drawTo(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(text);
}

void Button::draw(sf::RenderWindow& window) {
    shape.setFillColor(currentColor);
    window.draw(shape);
    window.draw(text);
}

void Button::update(sf::Vector2f mousePos) {
    sf::Color targetColor = theme.buttonColor;
    if (shape.getGlobalBounds().contains(mousePos)) {
        targetColor = theme.hoverColor;
    }
    float factor = 0.1f;
    currentColor.r += (targetColor.r - currentColor.r) * factor;
    currentColor.g += (targetColor.g - currentColor.g) * factor;
    currentColor.b += (targetColor.b - currentColor.b) * factor;
}

bool Button::isClicked(sf::Vector2f mousePos) {
    return shape.getGlobalBounds().contains(mousePos);
}

std::string Button::getLabel() const {
    return text.getString();
}

void Button::setButtonColor(sf::Color color) {
    shape.setFillColor(color);
}

bool Button::isMouseOver(sf::RenderWindow &window) {
    float xMouse = sf::Mouse::getPosition(window).x;
    float yMouse = sf::Mouse::getPosition(window).y;

    float topLeftX = shape.getPosition().x;
    float topLeftY = shape.getPosition().y;

    float limitRangeX = topLeftX + shape.getLocalBounds().width;
    float limitRangeY = topLeftY + shape.getLocalBounds().height;

    if (topLeftX < xMouse && xMouse < limitRangeX && topLeftY < yMouse && yMouse < limitRangeY) {
        return true;
    }
    return false;
}
