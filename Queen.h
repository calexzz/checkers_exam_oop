#ifndef CHECKERS_QUEEN_H
#define CHECKERS_QUEEN_H
#include "Color.h"
#include "Figure.h"


class Queen : public Figure {
    public:
    Queen(Color color) : Figure(color) {}
    std::vector<Move> getMoves(Board &board, Cell* myCell) override;
};


#endif //CHECKERS_QUEEN_H