#include "GameManager.h"

int main() {
    GameManager game;
    game.initWindow();
    
    while (game.isWindowOpen()) {
        game.clearScreen();
        game.pollEvents();
        game.update();
        game.draw();
        game.getRenderWindow().display();
    }
    return 0;
}
