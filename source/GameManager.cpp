#include "GameManager.h"

// GameManager::GameManager()
//     : window(sf::VideoMode(windowWidth, windowHeight), "Snake Game"),
//       snake(sf::Vector2f(cols / 2 * tileSize, rows / 2 * tileSize)),
//       food(cols, rows, tileSize) {
//     window.setFramerateLimit(10); // Set frame rate limit to match snake speed
// }

GameManager::~GameManager() {
    // Destructor can be used for cleanup if needed
}

void GameManager::initWindow() {
    this->window.create(sf::VideoMode(windowWidth, windowHeight), "Snake Game", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(10); // Set frame rate limit to match snake speed
}

void GameManager::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    this->snake.setDirection(UP);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  this->snake.setDirection(DOWN);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  this->snake.setDirection(LEFT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) this->snake.setDirection(RIGHT);
}

void GameManager::update() 
{
    // Di chuyển
    this->snake.move();

    sf::Vector2f head = snake.getHeadPosition();
    sf::Vector2f foodPos = food.getPosition();

    if ((int)head.x == (int)foodPos.x && (int)head.y == (int)foodPos.y) {
        snake.grow();
        food.spawn();
    }

    // Kiểm tra va chạm tường
    head = snake.getHeadPosition();
    if (head.x < 0 || head.x >= cols || head.y < 0 || head.y >= rows) {
        this->snake.reset(sf::Vector2f(cols / 2, rows / 2), RIGHT);
    }

    // Kiểm tra tự đâm
    if (snake.checkSelfCollision()) {
        this->snake.reset(sf::Vector2f(cols / 2, rows / 2), RIGHT);
    }
}

void GameManager::draw() 
{
    this->window.clear(sf::Color::Black);
    this->snake.draw(window, tileSize);
    this->food.draw(window, tileSize);
    this->window.display();
}

void GameManager::spawnFood() 
{
    this->food.spawn();
}

sf::RenderWindow& GameManager::getRenderWindow() 
{
    return this->window;
}

void GameManager::clearScreen() {
    this->window.clear(sf::Color::Black);
}

void GameManager::pollEvents() {
    sf::Event event;
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window.close();
        }
    }
}

bool GameManager::isWindowOpen()
{
    return this->window.isOpen();
}

void GameManager::run() {
    while (this->window.isOpen()) {
        this->pollEvents();
        this->handleInput();
        this->update();
        this->draw();
    }
}

void GameManager::resetGame() 
{
    this->snake.reset(sf::Vector2f(cols / 2, rows / 2), RIGHT);
    this->spawnFood();
}

void GameManager::start() {
    this->resetGame();
    this->run();
}