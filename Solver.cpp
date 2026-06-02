#include "Solver.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "Move.h"
#include "Board.h"
#include "Result.h"

using namespace std;

vector<Move> Solver::solve() {
    Result result = findWinningLine(depth, WHITE);
    if (result == WHITE_WINS) {
        winner = WHITE;
        // переворачиваем - ходы были в обратном порядке
        reverse(solution.begin(), solution.end());
    } else if (result == BLACK_WINS) {
        winner = BLACK;
        reverse(solution.begin(), solution.end());
    }
    return solution;
}

Result Solver::findWinningLine(int currentDepth, Color currentColor) {
    // проверяем условие победы
    if (board.noFigures(BLACK)) return WHITE_WINS; // черных нет - белые выиграли
    if (board.noFigures(WHITE)) return BLACK_WINS; // белых нет - черные выиграли
    if (currentDepth == 0) return NO_RESULT; // выигрыша нет

    vector<Move> moves = board.getAllMoves(currentColor);
    if (moves.empty()) return NO_RESULT;

    // перебираем все возможные ходы текущего цвета
    for (Move& move : moves) {
        if (move.src == move.dst) continue;
        if (move.src->figure == nullptr) continue;

        size_t sizeBefore = solution.size();

        board.applyMove(move); // делаем ход

        // определяем чей следующий код
        Color nextColor = (currentColor == WHITE) ? BLACK : WHITE;

        // рекурсивно ищем выигрыш на глубину-1 для следующего цвета
        Result result = findWinningLine(currentDepth-1, nextColor);

        // отменяем ход - возвращем доску как было
        board.undoMove(move);

        // если нашли победную ветку - запоминаем ход и возвращаем результат
        if (result == WHITE_WINS || result == BLACK_WINS) {
            solution.push_back(move);
            return result;
        }

        solution.resize(sizeBefore);
    }
    return NO_RESULT; // ни один ход не привёл к победе
}
