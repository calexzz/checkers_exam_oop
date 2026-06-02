#ifndef CHECKERS_BOARD_H
#define CHECKERS_BOARD_H
#include "Cell.h"
#include "Move.h"
#include "Color.h"
#include <vector>
#include <string>

class Board {
    Cell cells[8][8];
    bool loadPieces(std::ifstream& file, Color color); // вызывается внутри класса Board
public:
    Board();
    void loadFromFile(const std::string& filename);
    void applyMove(Move& move);
    void undoMove(Move& move);
    std::vector<Move> getAllMoves(Color color);
    bool needsPromotion(Cell* cell);
    void promote(Cell* cell);
    bool noFigures(Color color);
    Cell* getCell(int x, int y);
    bool inBounds(int x, int y);
};


#endif //CHECKERS_BOARD_H