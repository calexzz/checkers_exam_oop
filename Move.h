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

    std::vector<Cell*> captured; // координаты клеток где стояли срубленные фигуры
    std::vector<Figure*> figures; // сами объекты срубленных фигур

    std::vector<Cell*> path;  // промежуточные клетки при серии взятий

    bool wasPromotion;
};

#endif //CHECKERS_MOVE_H