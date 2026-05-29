#ifndef CHECKERS_MOVE_H
#define CHECKERS_MOVE_H

class Figure;
class Cell;

struct Move {
    Cell* src;
    Cell* dst;
    Cell* captured;
    bool wasPromotion;
    Figure* capturedFigure;
};

#endif //CHECKERS_MOVE_H