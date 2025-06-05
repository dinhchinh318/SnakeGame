#include "GameManager.h"

GameManager::~GameManager() {
    if (this->menu)
        delete this->menu;
    if (this->setting)
        delete this->setting;
    if (this->game)
        delete this->game;
}

// Initialize
void GameManager::initWindow() {
    this->window.create(sf::VideoMode(windowWidth, windowHeight), "Snake Game", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(10);

    sf::Font font;
    font.loadFromFile("assets/Fonts/arial.ttf");

    initMenuState();
    initGameState();

    this->currentState = this->menu;
}

void GameManager::initMenuState(){
    this->menu = new MenuState;
    this->menu->init(this);
}

void GameManager::initGameState(){
    this->game = new GameState;
    this->game->init(this);
}

void GameManager::initSettingState(){
    this->setting = new SettingState;
    this->setting->init(this);
}

// Getter / Setter states
void GameManager::setState(WindowState *state){
    this->currentState = state;
}

MenuState* GameManager::getMenuState(){
    return this->menu;
}

SettingState* GameManager::getSettingState(){
    return this->setting;
}

GameState* GameManager::getGameState(){
    return this->game;
}

WindowState* GameManager::getCurrentState(){
    return this->currentState;
}

// Clear screen
void GameManager::clearScreen() {
    this->window.clear(sf::Color::Black);
}

// Draw state
void GameManager::drawCurrentState(){
    this->currentState->draw(this);
}

// RenderWindow
sf::RenderWindow& GameManager::getRenderWindow() 
{
    return this->window;
}

void GameManager::update() {
    this->currentState->update(this);
}

void GameManager::pollEvents() {
    this->currentState->pollEvents(this);
}

void GameManager::draw(){
    this->drawCurrentState();
}

bool GameManager::isWindowOpen()
{
    return this->window.isOpen();
}