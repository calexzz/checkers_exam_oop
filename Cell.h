#ifndef CHECKERS_CELL_H
#define CHECKERS_CELL_H
#include "Color.h"

class Figure;

struct Cell {
    int x, y;
    Figure* figure;

    bool isEmpty();
    bool hasEnemy(Color color);
};

#endif //CHECKERS_CELL_H