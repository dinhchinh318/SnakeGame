#include "GameManager.h"

int main() {
    GameManager game;

    game.setLevel(numberLevel::L1);

    game.initWindow();
    game.start();

    return 0;
}
