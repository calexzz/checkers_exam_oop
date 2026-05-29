#include "Cell.h"
#include "Figure.h"

bool Cell::isEmpty() {
    return figure == nullptr;
}

bool Cell::hasEnemy(Color color) {
    return figure != nullptr && figure->color != color;
}