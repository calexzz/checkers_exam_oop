#include "Queen.h"
#include "Color.h"
#include "Board.h"
#include "Move.h"
#include "Cell.h"
#include <vector>

using namespace std;

std::vector<Move> Queen::getMoves(Board &board, Cell* myCell) {
    vector<Move> moves;
    vector<Move> capturedMoves;

    int dx[] = {-1, -1, 1, 1};
    int dy[] = {-1, 1, -1, 1};

    for (int i = 0; i < 4; i++) {
        int newX = myCell->x + dx[i];
        int newY = myCell->y + dy[i];

        while (board.inBounds(newX, newY)) {
            Cell* target = board.getCell(newX, newY);
            if (target->isEmpty()) {
                Move move;
                move.src = myCell;
                move.dst = target;
                move.captured = nullptr;
                moves.push_back(move);
            }else if (target->hasEnemy(color)) {
                int jumpX = newX + dx[i];
                int jumpY = newY + dy[i];

                if (board.inBounds(jumpX, jumpY) && board.getCell(jumpX, jumpY)->isEmpty()) {
                    Move captureMove;
                    captureMove.src = myCell;
                    captureMove.dst = board.getCell(jumpX, jumpY);
                    captureMove.captured = target;
                    capturedMoves.push_back(captureMove);
                }
                break;
            }else {
                break;
            }
            newX += dx[i];
            newY += dy[i];
        }
    }
    if (!capturedMoves.empty()) return capturedMoves;
    return moves;
}