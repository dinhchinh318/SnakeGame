#include "Direction.h"

bool isOpposite(Direction a, Direction b) {
    return (a == UP && b == DOWN) || (a == DOWN && b == UP) ||
           (a == LEFT && b == RIGHT) || (a == RIGHT && b == LEFT);
}