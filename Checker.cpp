#include "Checker.h"
#include "Color.h"
#include "Board.h"
#include "Move.h"
#include "Cell.h"
#include <vector>

using namespace std;

// вспомогательная рекурсивная функция для поиска взятий
void findCaptures(Board& board, Cell* current, Move currentMove, vector<Move>& result) {
    bool found = false; // нашли ли хоть одно взятие с текущей позиции
    const int dx[] = {-1, 1};

    for (int i = 0; i < 2; i++) {
        for (int dy : {1, -1}) {
            // координаты клетки где должен стоять враг
            int ex = current->x + dx[i];
            int ey = current->y + dy;

            if (!board.inBounds(ex, ey)) continue; // выход за пределы поля
            Cell* enemy = board.getCell(ex, ey);
            if (!enemy->hasEnemy(currentMove.moveColor)) continue; // нет врага - пропускаем

            // координаты клетки куда приземлимся после прыжка
            int lx = ex + dx[i];
            int ly = ey + dy;

            if (!board.inBounds(lx, ly)) continue; // выход за пределы поля
            Cell* landing = board.getCell(lx, ly);
            if (!landing->isEmpty()) continue; // клетка занята - пропускаем

            found = true;

            // сохраняем врага для восстановления
            Figure* savedEnemy = enemy->figure;

            // создаем новый ход с учетом текущего прыжка
            Move newMove = currentMove;
            newMove.dst = landing;
            newMove.captured.push_back(enemy); // запоминаем срубленную клетку
            newMove.path.push_back(landing); // запоминаем промежуточную позицию

            // временно прыгаем
            landing->figure = current->figure;
            current->figure = nullptr;
            enemy->figure = nullptr; // убираем врага

            // рекурсивно ищем продолжение серии с новой позиции
            findCaptures(board, landing, newMove, result);

            // отменяем прыжок - возвращаем доску как было
            current->figure = landing->figure;
            landing->figure = nullptr;
            enemy->figure = savedEnemy;
        }
    }

    // дальше бить нельзя - серия завершена
    // добавляем накопленный ход в результат если было хоть одно взятие
    if (!found && !currentMove.captured.empty()) {
        result.push_back(currentMove);
    }

}

vector<Move> Checker::getMoves(Board &board, Cell* myCell) {
    vector<Move> moves; // обычные ходы
    vector<Move> capturedMoves; // ходы со взятием

    // определяем направление для шашки по цвету (вверх для белых и вниз для черных)
    int y_direction = (color == WHITE) ? 1 : -1;
    const int x_direction[] = {-1, 1}; // левая и правая диагональ

    // ищем серии взятий
    Move startMove;
    startMove.src = myCell;
    startMove.dst = myCell; // обновится при вызове findCaptures
    startMove.moveColor = color;
    findCaptures(board, myCell, startMove, capturedMoves);

    // если есть взятия — возвращаем только их (обязательное взятие)
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