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

Result Solver::findWinningLine(int depth, Color color) {
    // проверяем условие победы
    if (board.noFigures(BLACK)) return WHITE_WINS; // черных нет - белые выиграли
    if (board.noFigures(WHITE)) return BLACK_WINS; // белых нет - черные выиграли
    if (depth == 0) return NO_RESULT; // выигрыша нет

    vector<Move> moves = board.getAllMoves(color);
    if (moves.empty()) return NO_RESULT; // ходов нет - выигрыша нет

    // перебираем все возможные ходы текущего цвета
    for (Move& move : moves) {
        board.applyMove(move); // делаем ход

        // определяем чей следующий код
        Color nextColor = (color == WHITE) ? BLACK : WHITE;

        // рекурсивно ищем выигрыш на глубину-1 для следующего цвета
        Result result = findWinningLine(depth-1, nextColor);

        // отменяем ход - возвращем доску как было
        board.undoMove(move);

        // если нашли победную ветку - запоминаем ход и возвращаем результат
        if (result == WHITE_WINS || result == BLACK_WINS) {
            solution.push_back(move);
            return result;
        }
    }

    return NO_RESULT; // ни один ход не привёл к победе
}
