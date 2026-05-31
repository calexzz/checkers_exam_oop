#include "Checker.h"
#include "Color.h"
#include "Board.h"
#include "Move.h"
#include "Cell.h"
#include <vector>

using namespace std;

void findCaptures(Board& board, Cell* current, Move currentMove, vector<Move>& result) {
    bool found = false; // по умолчанию - взятий не найдено
    const int dx[] = {-1, 1};

    for (int i = 0; i < 2; i++) {
        for (int dy : {1, -1}) {
            int ex = current->x + dx[i];
            int ey = current->y + dy;

            if (!board.inBounds(ex, ey)) continue;
            Cell* enemy = board.getCell(ex, ey);
            if (!enemy->hasEnemy(currentMove.moveColor)) continue;

            int lx = ex + dx[i];
            int ly = ey + dy;

            if (!board.inBounds(lx, ly)) continue;
            Cell* landing = board.getCell(lx, ly);
            if (!landing->isEmpty()) continue;

            found = true;

            // сохраняем врага
            Figure* savedEnemy = enemy->figure;

            // обновляем ход
            Move newMove = currentMove;
            newMove.dst = landing;
            newMove.captured.push_back(enemy);
            newMove.path.push_back(landing);

            // временно прыгаем
            landing->figure = current->figure;
            current->figure = nullptr;
            enemy->figure = nullptr;

            // рекурсия
            findCaptures(board, landing, newMove, result);

            // отменяем
            current->figure = landing->figure;
            landing->figure = nullptr;
            enemy->figure = savedEnemy;
        }
    }

    // дальше бить нельзя - серия завершена
    if (!found && !currentMove.captured.empty()) {
        result.push_back(currentMove);
    }

}

vector<Move> Checker::getMoves(Board &board, Cell* myCell) {
    vector<Move> moves;
    vector<Move> capturedMoves; // ходы со взятием

    // определяем направление для шашки по цвету (вверх для белых и вниз для черных)
    int y_direction = (color == WHITE) ? 1 : -1;
    const int x_direction[] = {-1, 1}; // левая и правая диагональ

    // ищем серии взятий
    Move startMove;
    startMove.src = myCell;
    startMove.dst = myCell;
    startMove.moveColor = color;
    findCaptures(board, myCell, startMove, capturedMoves);

    if (!capturedMoves.empty()) return capturedMoves;

    for (int i = 0; i < 2; i++) {
        // обычный ход - только вперёд
        int newX = myCell->x + x_direction[i];
        int newY = myCell->y + y_direction;

        if (board.inBounds(newX, newY)) {
            Cell* target = board.getCell(newX, newY);
            if (target->isEmpty()) {
                Move move;
                move.src = myCell;
                move.dst = target;
                move.moveColor = color;
                moves.push_back(move);
            }
        }
    }
    return moves;
}