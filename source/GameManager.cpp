#include "GameManager.h"

GameManager::~GameManager() {
    if (this->menu)
        delete this->menu;
    if (this->setting)
        delete this->setting;
    if (this->game)
        delete this->game;
}

void GameManager::initializePopups(
    Popup& p,
    int popupWidth, int popupHeight, 
    const std::string& title,
    const std::string& content,
    const std::vector<std::string>& ch,
    sf::Font& font,
    int buttonWidth, int buttonHeight
) {
    int popupX = (windowWidth - popupWidth) / 2;
    int popupY = (windowHeight - popupHeight) / 2;

    p = Popup(
        sf::Vector2f(float(popupWidth), float(popupHeight)),
        sf::Vector2f(float(popupX), float(popupY)), ch.size());

    p.setBackgroundColor(sf::Color(20, 15, 30, 220));
    p.frame.setOutlineThickness(4);
    p.frame.setOutlineColor(sf::Color(255, 255, 255, 180));
    
    p.setFont(font);
    p.setTextColor(sf::Color::White);
    p.setTextSize(30);
    p.setTitle(title);
    p.setContent(content);

    p.setChoiceButtonSize(buttonWidth, buttonHeight);

    for (int i = 0; i < ch.size(); ++i) {
        p.setChoiceString(ch[i], i);
        p.choices[i].setBackgroundColor(sf::Color(130, 90, 255, 230));
        p.choices[i].setTextColor(sf::Color::White);
        p.choices[i].setTextSize(22);
    }

    p.setPosition(float(popupX), float(popupY));
}


void GameManager::initWindow() {
    this->window.create(sf::VideoMode(windowWidth, windowHeight), "Snake Game", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(10);

    sf::Font font;
    font.loadFromFile("assets/Fonts/arial.ttf");

    initMenuState();

    this->currentState = this->menu;

    // Initialize popups
    initializePopups(
        gameOverPopup,
        400, 240,
        "GAME OVER!",
        "You lose",
        {"Try again", "Quit"}, font, 140, 46);

    initializePopups(
        winPopup,
        400, 240,
        "VICTORY!",
        "You win",
        {"Try again", "Quit"}, font,  140, 46);

}

void GameManager::update() {
    if (!showGameOverPopup && !showWinPopup) {
        updateGameLogic();
        checkGameOver();
        checkLevelComplete();
    }
    updatePopups();
}

void GameManager::updateGameLogic() {
    sf::Vector2i stPort = currentLevel->getStartPort();
    sf::Vector2i tail = snake.getTailPosition();
    std::vector<sf::Vector2i> obstacles = currentLevel ? currentLevel->getObstacles() : std::vector<sf::Vector2i>();

    if (tail == stPort) {
        obstacles.push_back(stPort);
        currentLevel->addObstacle(stPort);
    }
    this->snake.move();

    sf::Vector2i head = snake.getHeadPosition();
    sf::Vector2i foodPos = food.getPosition();

    if ((int)head.x == (int)foodPos.x && (int)head.y == (int)foodPos.y) {
        if (drawFood) {
            foodEaten++;
            snake.grow();
        }
        if (foodEaten < currentLevel->getFoodGoal()) {
            food.spawn(obstacles, this->snake.getSnake(), cols, rows);
        } else {
            drawFood = false;
        }
    }
}

void GameManager::checkGameOver() {
    sf::Vector2i head = snake.getHeadPosition();
    std::vector<sf::Vector2i> obstacles = currentLevel ? currentLevel->getObstacles() : std::vector<sf::Vector2i>();

    // Chạm tường/obstacle
    for (const auto& obs : obstacles) {
        if ((int)head.x == obs.x && (int)head.y == obs.y) {
            foodEaten = 0;
            showGameOverPopup = true;
            return;
        }
    }

    // Tự đâm thân mình
    if (snake.checkSelfCollision()) {
        foodEaten = 0;
        showGameOverPopup = true;
        return;
    }
}

void GameManager::checkLevelComplete() {
    if (currentLevel && foodEaten >= currentLevel->getFoodGoal()) {
        sf::Vector2i otPort = currentLevel->getOutPort();
        currentLevel->deleteObstacle(otPort);
        sf::Vector2i tail = snake.getTailPosition();

        if (tail == otPort) {
            foodEaten = 0;
            int nextLevelInt = static_cast<int>(currentLevel->getLevelNumber()) + 1;
            if (nextLevelInt >= 4) {
                showWinPopup = true;
            } else {
                this->setLevel(static_cast<numberLevel>(nextLevelInt));
                this->snake.setSnakePos(currentLevel->getStartPort());
                drawFood = true;
                std::vector<sf::Vector2i> obstacles = currentLevel ? currentLevel->getObstacles() : std::vector<sf::Vector2i>();
                this->food.spawn(obstacles, this->snake.getSnake(), cols, rows);
                std::cout << "Chuyen sang level: " << static_cast<int>(currentLevel->getLevelNumber()) + 1 << std::endl;
            }
        }
    }
}

void GameManager::updatePopups() {
    // Nếu muốn hiệu ứng hover/animation thì xử lý ở đây
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
    winPopup.update(mousePos);
    gameOverPopup.update(mousePos);
}


void GameManager::draw() 
{
    this->window.clear(sf::Color::Black);
    this->drawYard(this->window, tileSize, rows, cols);

    if (this->currentLevel) {
        this->currentLevel->draw(window, tileSize); // VẼ TƯỜNG BAO/OBSTACLE
    }
    this->snake.draw(window, tileSize);
    if (drawFood){
        this->food.draw(window, tileSize);
    }

    if (this->showGameOverPopup) {
        this->gameOverPopup.drawTo(window);
    }
    if (this->showWinPopup) {
        this->winPopup.drawTo(window);
    }

    this->window.display();
}

void GameManager::drawYard(sf::RenderWindow& window, int tileSize, int rows, int cols)
{
    // load snake image
    yardTexture.loadFromFile("assets/picture/yard.jpg");

    yardSprite.setTexture(yardTexture);
    //

    yardSprite.setOrigin(yardTexture.getSize().x / 2.f, yardTexture.getSize().y / 2.f);
    //

    yardSprite.setTexture(yardTexture);
    yardSprite.setOrigin(0, 0); // Gốc trái trên
    sf::Vector2u texSize = yardTexture.getSize();
    float scaleX = tileSize / static_cast<float>(texSize.x);
    float scaleY = tileSize / static_cast<float>(texSize.y);
    yardSprite.setScale(scaleX, scaleY);

    // Vẽ toàn bộ sàn theo ma trận (rows x cols)
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            yardSprite.setPosition(x * tileSize, y * tileSize);
            window.draw(yardSprite);
        }
    }
}


void GameManager::spawnFood() 
{
    // Lấy danh sách các obstacles từ currentLevel
    std::vector<sf::Vector2i> obstacles = currentLevel ? currentLevel->getObstacles() : std::vector<sf::Vector2i>();

    this->food.spawn(obstacles, this->snake.getSnake(), cols, rows);
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
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window.close();
        }
        // ---- Xử lý NÚT popup trước ----
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

            // Chỉ xử lý khi popup đang mở
            if (showGameOverPopup) {
                if (gameOverPopup.choices[0].isClicked(mousePos)) {
                    showGameOverPopup = false;
                    resetGame();
                } else if (gameOverPopup.choices[1].isClicked(mousePos)) {
                    window.close();
                }
                // Không cho xử lý event khác nữa
                return;
            }
            if (showWinPopup) {
                if (winPopup.choices[0].isClicked(mousePos)) {
                    showWinPopup = false;
                    resetGame();
                } else if (winPopup.choices[1].isClicked(mousePos)) {
                    window.close();
                }
                // Không cho xử lý event khác nữa
                return;
            }
        }

        // ---- Chỉ xử lý phím di chuyển khi KHÔNG có popup ----
        if (event.type == sf::Event::KeyPressed) {
            if (!showGameOverPopup && !showWinPopup) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                    case sf::Keyboard::W:
                        snake.setDirection(UP);
                        break;
                    case sf::Keyboard::Down:
                    case sf::Keyboard::S:
                        snake.setDirection(DOWN);
                        break;
                    case sf::Keyboard::Left:
                    case sf::Keyboard::A:
                        snake.setDirection(LEFT);
                        break;
                    case sf::Keyboard::Right:
                    case sf::Keyboard::D:
                        snake.setDirection(RIGHT);
                        break;
                    default:
                        break;
                }
            }                 
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
        this->update();     
        this->draw();
    }
}

void GameManager::resetGame() 
{
    drawFood = true;
    this->setLevel(numberLevel::L1);
    this->snake.reset(currentLevel->getStartPort(), RIGHT);
    this->spawnFood();
}

void GameManager::start() {
    this->resetGame();
    this->run();
}

void GameManager::setLevel(numberLevel num) {
    currentLevel = LevelFactory::createLevel(num);
}

const Level& GameManager::getCurrentLevel() const { 
    return *currentLevel; 
}

void GameManager::initMenuState(){
    this->menu = new MenuState;
    this->menu->init(this);
}

void GameManager::setState(WindowState *state){
    this->currentState = state;
}

MenuState* GameManager::getMenuState(){
    return this->menu;
}

WindowState* GameManager::getCurrentState(){
    return this->currentState;
}