#include "Checker.h"
#include "Color.h"
#include "Board.h"
#include "Move.h"
#include "Cell.h"
#include <vector>

using namespace std;

vector<Move> Checker::getMoves(Board &board, Cell* myCell) {
    vector<Move> moves;
    vector<Move> capturedMoves; // ходы со взятием

    // определяем направление для шашки по цвету (вверх для белых и вниз для черных)
    int y_direction = (color == WHITE) ? 1 : -1;

    const int x_direction[] = {-1, 1}; // левая и правая диагональ

    for (int i = 0; i < 2; i++) {
        int newX = myCell->x + x_direction[i];
        int newY = myCell->y + y_direction;

        // проверяем, что в пределах доски
        if (!board.inBounds(newX, newY)) continue;

        Cell* target = board.getCell(newX, newY);
        if (target->isEmpty()) {
            Move move;
            move.src = myCell;
            move.dst = target;
            move.captured = nullptr;
            moves.push_back(move);
        } else if (target->hasEnemy(color)) {
            // может быть взятие - проверяем клетку за врагом
            int jumpX = newX + x_direction[i];
            int jumpY = newY + y_direction;

            if (board.inBounds(jumpX, jumpY) && board.getCell(jumpX, jumpY)->isEmpty()) {
                Move captureMove;
                captureMove.src = myCell;
                captureMove.dst = board.getCell(jumpX, jumpY);
                captureMove.captured = target;
                capturedMoves.push_back(captureMove);
            }
        }
    }
    if (!capturedMoves.empty()) return capturedMoves;
    return moves;
}