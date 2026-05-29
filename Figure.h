#ifndef CHECKERS_FIGURE_H
#define CHECKERS_FIGURE_H
#include <vector>

#include "Color.h"
#include "Move.h"

class Board;

class Figure {
public:
    Color color;
    Figure(Color color) : color(color) {}
    virtual std::vector<Move> getMoves(Board& board, Cell* myCell) = 0;
    virtual ~Figure() {}
};


#endif //CHECKERS_FIGURE_H