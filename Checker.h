#ifndef CHECKERS_CHECKER_H
#define CHECKERS_CHECKER_H
#include "Figure.h"

class Checker : public Figure {
    public:
    Checker(Color color) : Figure(color) {}
    std::vector<Move> getMoves(Board &board) override;
};

#endif //CHECKERS_CHECKER_H