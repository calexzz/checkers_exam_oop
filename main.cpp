#include <iostream>
#include "Game.h"

int main() {
    Game game("test.txt", 1);
    game.run();
    game.printResult();
    return 0;
}