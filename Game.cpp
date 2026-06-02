#include "Game.h"
#include <string>
#include <iostream>

using namespace std;

void Game::run() {
    if (board.noFigures(WHITE) || board.noFigures(BLACK)) {
        cout << "Позиция некорректна - решатель не запущен" << endl;
        return;
    }
    history = solver.solve();
}

void Game::printResult() {
    if (history.empty()) {
        cout << "Выигрыша нет" << endl;
        return;
    }

    for (Move& move : history) {
        string colorStr = (move.moveColor == WHITE) ? "Белые" : "Черные";

        char srcCol = 'A' + move.src->x;
        char srcRow = '1' + move.src->y;

        cout << colorStr << ": " << srcCol << srcRow;

        // выводим промежуточные клетки если есть серия взятий
        if (!move.path.empty()) {
            for (Cell* cell : move.path) {
                char col = 'A' + cell->x;
                char row = '1' + cell->y;
                cout << " -> " << col << row;
            }
        } else {
            // обычный ход — просто dst
            char dstCol = 'A' + move.dst->x;
            char dstRow = '1' + move.dst->y;
            cout << " -> " << dstCol << dstRow;
        }
        cout << endl;
    }

    cout << (solver.getWinner() == WHITE ? "Белые" : "Черные")
         << " выигрывают!" << endl;

}