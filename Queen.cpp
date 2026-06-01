#include "Queen.h"
#include "Color.h"
#include "Board.h"
#include "Move.h"
#include "Cell.h"
#include <vector>

using namespace std;

void findCapturesQueen(Board& board, Cell* current, Move currentMove, vector<Move>& result) {
    bool foundAny = false;

    // все 4 направления
    int dx[] = {-1, -1, 1,  1};
    int dy[] = {-1,  1, -1, 1};

    for (int i = 0; i < 4; i++) {
        // идём по диагонали пока пустые клетки или не край доски
        int x = current->x + dx[i];
        int y = current->y + dy[i];

        while (board.inBounds(x, y)) {
            Cell* cell = board.getCell(x, y);

            if (cell->isEmpty()) {
                // пустая — продолжаем идти
                x += dx[i];
                y += dy[i];
                continue;
            }

            if (cell->hasEnemy(currentMove.moveColor)) {
                // нашли врага — перебираем куда приземлиться
                int lx = x + dx[i];
                int ly = y + dy[i];

                while (board.inBounds(lx, ly) && board.getCell(lx, ly)->isEmpty()) {
                    foundAny = true;

                    Cell* landing = board.getCell(lx, ly);
                    Figure* savedEnemy = cell->figure; // сохраняем врага для восстановления

                    // создаем новый ход с учетом текущего прыжка
                    Move newMove = currentMove;
                    newMove.dst = landing;
                    newMove.captured.push_back(cell); // запоминаем срубленную клетку
                    newMove.path.push_back(landing); // запоминаем промежуточную позицию

                    // временно прыгаем
                    landing->figure = current->figure;
                    current->figure = nullptr;
                    cell->figure = nullptr; // временно убираем врага

                    // рекурсивно ищем продолжение серии с новой позиции
                    findCapturesQueen(board, landing, newMove, result);

                    // отменяем прыжок
                    current->figure = landing->figure;
                    landing->figure = nullptr;
                    cell->figure = savedEnemy;

                    // переходим к следующей клетке приземления
                    lx += dx[i];
                    ly += dy[i];
                }
                break; // после врага дальше по этой диагонали не идем
            }
            break; // своя фигура — стоп
        }
    }

    // серия завершена - добавляем если было хоть одно взятие
    if (!foundAny && !currentMove.captured.empty()) {
        result.push_back(currentMove);
    }
}

std::vector<Move> Queen::getMoves(Board &board, Cell* myCell) {
    vector<Move> moves;
    vector<Move> capturedMoves;

    // ищем серии взятий
    Move startMove;
    startMove.src = myCell;
    startMove.dst = myCell;
    startMove.moveColor = color;
    findCapturesQueen(board, myCell, startMove, capturedMoves);

    // если есть взятия - возвращаем только их
    if (!capturedMoves.empty()) return capturedMoves;

    // обычные ходы дамки
    int dx[] = {-1, -1, 1, 1};
    int dy[] = {-1, 1, -1, 1};

    for (int i = 0; i < 4; i++) {
        int newX = myCell->x + dx[i];
        int newY = myCell->y + dy[i];

        while (board.inBounds(newX, newY)) {
            Cell* target = board.getCell(newX, newY);

            if (target->isEmpty()) {
                // пустая клетка - добавляем ход и идём дальше
                Move move;
                move.src = myCell;
                move.dst = target;
                move.moveColor = color;
                moves.push_back(move);
                newX += dx[i];
                newY += dy[i];
            } else {
                // на клетке есть фигура
                break;
            }
        }
    }
    return moves;
}