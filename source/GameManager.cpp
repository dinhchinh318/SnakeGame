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
    gameOver = false;
    this->window.create(sf::VideoMode(windowWidth, windowHeight), "Snake Game", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(10); // Set frame rate limit to match snake speed
}

void GameManager::update() 
{
    // Di chuyển
    this->snake.move();
    
    sf::Vector2i head = snake.getHeadPosition();
    sf::Vector2i foodPos = food.getPosition();

    // Lấy danh sách các obstacles từ currentLevel
    std::vector<sf::Vector2i> obstacles = currentLevel ? currentLevel->getObstacles() : std::vector<sf::Vector2i>();

    if ((int)head.x == (int)foodPos.x && (int)head.y == (int)foodPos.y) {
        foodEaten++;
        if (currentLevel && foodEaten >= currentLevel->getFoodGoal()) {
            // Kiểm tra win game
            if (static_cast<int>(currentLevel->getLevelNumber()) == 2){
                std::cout << "You won" << std::endl;
                return;
            }
            // Nếu ăn đủ thức ăn, chuyển sang level tiếp theo
            foodEaten = 0; // Reset số lượng thức ăn đã ăn
            this->setLevel(static_cast<numberLevel>(static_cast<int>(currentLevel->getLevelNumber()) + 1));
            std::cout << "Chuyển sang level tiếp theo: " << static_cast<int>(currentLevel->getLevelNumber()) << std::endl;
            //this->resetGame();
            return; // Thoát hàm để tránh vẽ thức ăn mới
        }
        snake.grow();
        food.spawn(obstacles, this->snake.getSnake(), cols, rows); // Sinh thức ăn mới
    }

    // Kiểm tra chạm tường
    head = snake.getHeadPosition();
    for (const auto& obs : obstacles) {
        if ((int)head.x == obs.x && (int)head.y == obs.y) {
            // // Chạm tường, reset hoặc kết thúc game
            // foodEaten = 0;
            // this->snake.reset(sf::Vector2i(cols / 2, rows / 2), RIGHT);
            // food.spawn(obstacles, this->snake.getSnake(), cols, rows);
            // break; // Thoát vòng lặp cho an toàn
            foodEaten = 0;
            gameOver = true;
            return;
        }
    }

    // Kiểm tra tự đâm
    if (snake.checkSelfCollision()) {
        // foodEaten = 0;
        // this->snake.reset(sf::Vector2i(cols / 2, rows / 2), RIGHT);
        // food.spawn(obstacles, this->snake.getSnake(), cols, rows);
        foodEaten = 0;
        gameOver = true;
        return;
    }
}

void GameManager::draw() 
{
    this->window.clear(sf::Color::Black);
    if (currentLevel) {
        currentLevel->drawObstacles(window, tileSize); // VẼ TƯỜNG BAO/OBSTACLE
    }
    this->snake.draw(window, tileSize);
    this->food.draw(window, tileSize);
    if (gameOver == true) {
        sf::Font font;
        if (font.loadFromFile("assets/Fonts/arial.ttf")) {
            sf::Text text("GAME OVER\nPress R to Restart", font, 32);
            text.setFillColor(sf::Color::White);
            text.setPosition(50, cols * tileSize / 2 - 50);
            window.draw(text);
        }
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
            if (gameOver == false){
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
            else {        
                if (event.key.code == sf::Keyboard::R) {
                    this->resetGame();
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
        if (gameOver == false){
            this->update();
        }
        this->draw();
    }
}

void GameManager::resetGame() 
{
    gameOver = false;
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