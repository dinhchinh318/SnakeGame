#include "MenuState.h"
#include "GameManager.h"
#include <iostream>

MenuState::MenuState(){}

void MenuState::pollEvents(GameManager* gameMan) {
    sf::Event event;
    while (gameMan->getRenderWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gameMan->getRenderWindow().close();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            switch(this->currentChoice) {
                case 0:
                    std::cout << "[MenuState] -> New Game Selected" << std::endl;
                    gameMan->clearScreen();
                    gameMan->initGameState();            // XÓA và tạo mới GameState
                    gameMan->setState(gameMan->getGameState()); // CHUYỂN state sang GameState
                    break;
                case 1:
                    std::cout << "[MenuState] -> Setting Selected" << std::endl;
                    gameMan->clearScreen();
                    gameMan->setState(gameMan->getSettingState());
                    break;
                case 2:
                    std::cout << "[MenuState] -> Exit Selected" << std::endl;
                    gameMan->getRenderWindow().close();
                    break;
                default:
                    break;
            }
        }
    }

    for (int i = 0; i < this->numberOfButtons; ++i) {
        if (button[i].isMouseOver(gameMan->getRenderWindow())) {
            currentChoice = i;
            update(gameMan);
            break;
        }
        currentChoice = -1;
    }
}

void MenuState::init(GameManager* gameMan) {
    if (!font.loadFromFile("assets/Fonts/arial.ttf")) {}

    float winWidth = gameMan->getRenderWindow().getSize().x;
    float winHeight = gameMan->getRenderWindow().getSize().y;

    this->background.setSize(sf::Vector2f(winWidth, winHeight));
    this->bg_texture.loadFromFile("assets/picture/menu.jpg");
    background.setTexture(&this->bg_texture);

    // Game Title
    this->gameTitle.setString("Snake Game");
    this->gameTitle.setCharacterSize(40);
    this->gameTitle.setFont(this->font);
    this->gameTitle.setFillColor(sf::Color::Yellow);
    this->gameTitle.setOrigin(this->gameTitle.getLocalBounds().width / 2,
                                this->gameTitle.getLocalBounds().height / 2);
    this->gameTitle.setPosition(winWidth / 2, winHeight / 2 - 120); // Đặt cao hơn để chừa chỗ cho nút

    this->currentChoice = 0;
    button[0].setTitle("New Game");
    button[1].setTitle("Setting");
    button[2].setTitle("Exit");

    this->numberOfButtons = 3;
    float buttonSpacing = 60.f;
    float buttonStartY = this->gameTitle.getPosition().y + 80.f;

    for (int i = 0; i < this->numberOfButtons; ++i) {
        button[i].setSize(200, 50);
        button[i].setBackgroundColor(sf::Color(0, 0, 0, 0));
        button[i].setTextColor(sf::Color::Black);
        button[i].setFont(this->font);
        button[i].setTextSize(30);
        button[i].setPosition(winWidth / 2 - 100.0f, buttonStartY + i * buttonSpacing);
    }
}


void MenuState::draw(GameManager* gameMan) {
    gameMan->getRenderWindow().draw(this->background);
    gameMan->getRenderWindow().draw(this->gameTitle);

    for (int i = 0; i < this->numberOfButtons; ++i) {
        button[i].draw(gameMan->getRenderWindow());
    }
}

void MenuState::update(GameManager* gameMan) {
    for (int i = 0; i < 3; ++i) {
        // button[i].update(mousePos);
        button[i].setTextSize(20);
        button[i].setTextColor(sf::Color::White);
        button[i].setOriginToCenterForText();
        if (i == currentChoice)
        {
            button[i].setTextSize(25);
            button[i].setTextColor(sf::Color::Green);
            button[i].setOriginToCenterForText();
        }
    }
}
