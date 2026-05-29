#ifndef CHECKERS_MOVE_H
#define CHECKERS_MOVE_H

class Cell;

struct Move {
    Cell* src;
    Cell* dst;
    Cell* captured;
};

#endif //CHECKERS_MOVE_H