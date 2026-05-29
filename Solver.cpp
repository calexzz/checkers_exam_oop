#include "Solver.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "Move.h"
#include "Board.h"

using namespace std;

vector<Move> Solver::solve() {
    findWinningLine(depth, WHITE);
    // ходы добавляются в обратном порядке, поэтому переворачиваем вектор ходов
    reverse(solution.begin(), solution.end());
    return solution;
}

bool Solver::findWinningLine(int depth, Color color) {
    if (depth == 0) return board.isWhiteWinning(); // выход из рекурсии

    // получаем все возможные ходы для текущего цвета
    vector<Move> moves = board.getAllMoves(color);

    // если ходов нет, то опрееляем победителя
    if (moves.empty()) {
        if (color == BLACK) return true; // черные не могут ходить - белые выиграли
        return false; // белые не могут ходить - проиграли
    }

    // перебираем все возможные ходы
    for (Move& move : moves) {
        board.applyMove(move); // делаем ход

        // Определяем чей следующий ход
        Color nextColor = (color == WHITE) ? BLACK : WHITE;

        // рекурсивно ищем выигрыш на глубину-1 для следующего цвета
        bool result = findWinningLine(depth-1, nextColor);

        // отменяем ход
        board.undoMove(move);

        // если нашли выигрышный ход, то запоминаем его
        if (result) {
            solution.push_back(move);
            return true;
        }
    }
    cout << "depth=" << depth << " color=" << color << " ходов=" << moves.size() << endl;
    return false;
}
