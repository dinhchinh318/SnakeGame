#include "GameManager.h"

// GameManager::GameManager()
//     : window(sf::VideoMode(windowWidth, windowHeight), "Snake Game"),
//       snake(sf::Vector2i(cols / 2 * tileSize, rows / 2 * tileSize)),
//       food(cols, rows, tileSize) {
//     window.setFramerateLimit(10); // Set frame rate limit to match snake speed
// }

GameManager::~GameManager() {
    // Destructor can be used for cleanup if needed
}

void GameManager::initWindow() {
    this->window.create(sf::VideoMode(windowWidth, windowHeight), "Snake Game", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(10);

    // Khởi tạo popup đẹp
    int popupWidth = 400, popupHeight = 240;
    int popupX = (windowWidth - popupWidth) / 2;
    int popupY = (windowHeight - popupHeight) / 2;

    // Game Over Popup
    gameOverPopup = Popup(
        sf::Vector2f(float(popupWidth), float(popupHeight)),
        sf::Vector2f(float(popupX), float(popupY)), 2);

    gameOverPopup.setBackgroundColor(sf::Color(20, 15, 30, 220));
    gameOverPopup.frame.setOutlineThickness(4);
    gameOverPopup.frame.setOutlineColor(sf::Color(255, 255, 255, 180));

    sf::Font font;
    font.loadFromFile("assets/Fonts/arial.ttf");
    gameOverPopup.setFont(font);
    gameOverPopup.setTextColor(sf::Color::White);
    gameOverPopup.setTextSize(30);
    gameOverPopup.setTitle("GAME OVER!");
    gameOverPopup.setContent("You lose");

    gameOverPopup.setChoiceButtonSize(140, 46);
    gameOverPopup.setChoiceString("Try again", 0);
    gameOverPopup.setChoiceString("Quit", 1);

    // Chỉnh màu button và gọi lại setPosition để căn giữa các nút
    for (int i = 0; i < 2; ++i) {
        gameOverPopup.choices[i].setBackgroundColor(sf::Color(130, 90, 255, 230));
        gameOverPopup.choices[i].setTextColor(sf::Color::White);
        gameOverPopup.choices[i].setTextSize(22);
    }
    // GỌI LẠI setPosition ĐỂ BUTTON LUÔN ĐỀU & GIỮA
    gameOverPopup.setPosition(float(popupX), float(popupY));

    // Win Popup
    winPopup = Popup(
        sf::Vector2f(float(popupWidth), float(popupHeight)),
        sf::Vector2f(float(popupX), float(popupY)), 2);

    winPopup.setBackgroundColor(sf::Color(20, 15, 30, 220));
    winPopup.frame.setOutlineThickness(4);
    winPopup.frame.setOutlineColor(sf::Color(255, 255, 255, 180));
    winPopup.setFont(font);
    winPopup.setTextColor(sf::Color::White);
    winPopup.setTextSize(30);
    winPopup.setTitle("VICTORY!");
    winPopup.setContent("You win");

    winPopup.setChoiceButtonSize(140, 46);
    winPopup.setChoiceString("Try again", 0);
    winPopup.setChoiceString("Quit", 1);

    for (int i = 0; i < 2; ++i) {
        winPopup.choices[i].setBackgroundColor(sf::Color(130, 90, 255, 230));
        winPopup.choices[i].setTextColor(sf::Color::White);
        winPopup.choices[i].setTextSize(22);
    }
    winPopup.setPosition(float(popupX), float(popupY));
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
        if (event.type == sf::Event::KeyPressed) {
            if (showGameOverPopup == false){
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

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
            if (this->gameOverPopup.choices[0].isClicked(mousePos)) {
                this->showGameOverPopup = false;
                this->resetGame();
            } else if (gameOverPopup.choices[1].isClicked(mousePos)) {
                this->window.close();
            }

            if (this->showWinPopup == true) {
                if (gameOverPopup.choices[0].isClicked(mousePos)) {
                    this->showWinPopup = false;
                    this->resetGame();
                } else if (this->gameOverPopup.choices[1].isClicked(mousePos)) {
                    this->window.close();
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