#ifndef CHECKERS_GAME_H
#define CHECKERS_GAME_H
#include "Board.h"
#include "Move.h"
#include "Solver.h"

class Game {
    Board board;
    Solver solver;
    std::vector<Move> history;
public:
    Game(const std::string& filename, int depth)
        : solver(board, depth) {
        board.loadFromFile(filename);
    }
    void run();
    void printResult();
};


#endif //CHECKERS_GAME_H