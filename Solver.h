#ifndef CHECKERS_SOLVER_H
#define CHECKERS_SOLVER_H
#include "Board.h"
#include "Move.h"
#include <vector>

class Solver {
    Board& board;
    int depth;
    std::vector<Move> solution;
public:
    Solver(Board& b, int depth) : board(b), depth(depth) {};
    std::vector<Move> solve();
    bool findWinningLine(int depth, Color color);
};


#endif //CHECKERS_SOLVER_H