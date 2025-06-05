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
        else if (event.type == sf::Event::MouseButtonPressed) {
            switch(this->currentChoice) {
                case 0:
                    std::cout << "Resume" << std::endl;
                    gameMan->clearScreen();
                    gameMan->setState(gameMan->getGameState());
                    gameMan->getGameState()->start(gameMan);
                    break;
                case 1:
                    std::cout << "New Game" << std::endl;
                    gameMan->clearScreen();
                    gameMan->setState(gameMan->getGameState());
                    gameMan->getGameState()->start(gameMan);
                    break;
                case 2:
                    std::cout << "Setting" << std::endl;
                    gameMan->clearScreen();
                    gameMan->setState(gameMan->getSettingState());
                    break;
                case 3:
                    std::cout << "Exit" << std::endl;
                    exit(2);
                    break;
                default:
                    break;
            }
        }
    }
    
    int i = gameMan->hasGameInProgress ? 0 : 1;
    for (; i < this->numberOfButtons; ++i)
    {
        if (button[i].isMouseOver(gameMan->getRenderWindow()))
        {
            currentChoice = i;
            update(gameMan);
            break;
        }
        currentChoice = -1;
    }
}

void MenuState::init(GameManager* gameMan) {
    if (!font.loadFromFile("assets/Fonts/arial.ttf")) {}

    this->background.setSize(sf::Vector2f(gameMan->getRenderWindow().getSize().x,
                                            gameMan->getRenderWindow().getSize().y));
    this->bg_texture.loadFromFile("assets/picture/menu.jpg");
    background.setTexture(&this->bg_texture);

    // Game Title
    this->gameTitle.setString("Snake Game");
    this->gameTitle.setCharacterSize(40);
    this->gameTitle.setFont(this->font);
    this->gameTitle.setFillColor(sf::Color::Yellow);
    this->gameTitle.setOrigin(this->gameTitle.getLocalBounds().width / 2,
                                this->gameTitle.getLocalBounds().height / 2);
    this->gameTitle.setPosition(gameMan->getRenderWindow().getSize().x / 2,
                                gameMan->getRenderWindow().getSize().y / 2);
    
    this->currentChoice = 0;
    button[0].setTitle("Resume");
    button[1].setTitle("New Game");
    button[2].setTitle("Setting");
    button[3].setTitle("Exit");

    this->numberOfButtons = 4;
    for (int i = 0; i < this->numberOfButtons; ++i) {
        button[i].setSize(150,30);
        button[i].setBackgroundColor(sf::Color(0, 0, 0, 0));
        button[i].setTextColor(sf::Color::Black);
        button[i].setFont(this->font);
        button[i].setTextSize(30);
        button[i].setPosition(gameMan->getRenderWindow().getSize().x / 2,
                                gameMan->getRenderWindow().getSize().y /2 - 60 + 45 * i);
    }

}

void MenuState::draw(GameManager* gameMan) {
    gameMan->getRenderWindow().draw(this->background);
    gameMan->getRenderWindow().draw(this->gameTitle);

    int i = gameMan->hasGameInProgress ? 0 : 1;
    for (; i < this->numberOfButtons; ++i) {
        button[i].drawTo(gameMan->getRenderWindow());
    }
}

void MenuState::update(GameManager* gameMan) {
    int i = gameMan->hasGameInProgress ? 0 : 1;
    for (; i < this->numberOfButtons; ++i){
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
