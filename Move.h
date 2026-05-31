#ifndef CHECKERS_MOVE_H
#define CHECKERS_MOVE_H
#include <vector>
#include "Color.h"

class Figure;
class Cell;

struct Move {
    Cell* src;
    Cell* dst;
    Color moveColor;
    std::vector<Cell*> captured;
    std::vector<Figure*> figures;
    std::vector<Cell*> path;
    bool wasPromotion;
};

#endif //CHECKERS_MOVE_H