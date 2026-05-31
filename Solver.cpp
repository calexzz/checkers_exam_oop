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
        reverse(solution.begin(), solution.end());
    } else if (result == BLACK_WINS) {
        winner = BLACK;
        reverse(solution.begin(), solution.end());
    }
    return solution;
}

Result Solver::findWinningLine(int depth, Color color) {
    if (board.noFigures(BLACK)) return WHITE_WINS;
    if (board.noFigures(WHITE)) return BLACK_WINS;
    if (depth == 0) return NO_RESULT;

    vector<Move> moves = board.getAllMoves(color);
    if (moves.empty()) return NO_RESULT;

    for (Move& move : moves) {
        board.applyMove(move);
        Color nextColor = (color == WHITE) ? BLACK : WHITE;
        Result result = findWinningLine(depth-1, nextColor);
        board.undoMove(move);

        if (result == WHITE_WINS || result == BLACK_WINS) {
            solution.push_back(move);
            return result;
        }
    }

    return NO_RESULT;
}
