#ifndef CHECKERS_SOLVER_H
#define CHECKERS_SOLVER_H
#include "Board.h"
#include "Move.h"
#include "Color.h"
#include "Result.h"
#include <vector>

class Solver {
    Board& board;
    int depth;
    std::vector<Move> solution;
    Color winner;
public:
    Solver(Board& b, int depth) : board(b), depth(depth) {};
    std::vector<Move> solve();
    Result findWinningLine(int currentDepth, Color currentColor);
    Color getWinner() {return winner;}
};


#endif //CHECKERS_SOLVER_H