#include "Game.h"
#include <iostream>

using namespace std;

void Game::run() {
    history = solver.solve();
}

void Game::printResult() {
    if (history.size() == 0) {
        cout << "История ходов пуста - выигрыша нет" << endl;
        return;
    }

    for (Move& move : history) {
        char srcCol = 'A' + move.src->x;
        char srcRow = '1' + move.src->y;

        char dstCol = 'A' + move.dst->x;
        char dstRow = '1' + move.dst->y;

        cout << srcCol << srcRow << " -> " << dstCol << dstRow << endl;
    }
}
