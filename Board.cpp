#include <iostream>
#include "Board.h"
#include <string>
#include <fstream>

#include "Checker.h"
#include "Queen.h"

using namespace std;

Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cells[i][j].x = i;
            cells[i][j].y = j;
            cells[i][j].figure = nullptr;
        }
    }
}

 bool Board::loadPieces(std::ifstream& file, Color color) {
    std::string label; // читаем "White:" или "Black:"
    int count; // количество фигур данного цвета

    // читаем
    file >> label >> count;

    if (count > 12) {
        cout << "Шашек одного цвета не может быть больше 12" << endl;
        return false;
    }

    for (int i = 0; i < count; i++) {
        std::string token;
        file >> token;

        char first = token[0];
        if (first != 'M' && (first < 'A' || first > 'H')) {
            cout << "Некорректная координата: " << token << endl;
            return false;
        }

        // если дамка - проверяем второй символ
        bool isQueen = false;
        if (first == 'M') {
            isQueen = true;
            char second = token[1];
            if (second < 'A' || second > 'H') {
                cout << "Некорректная координата дамки: " << token << endl;
                return false;
            }
        }

        std::string coord = isQueen ? token.substr(1) : token;

        // преобразуем координату из текста в индексы массива
        int x = coord[0] - 'A';
        int y = coord[1] - '1';

        if (!inBounds(x,y)) {
            cout << "Координаты фигуры за пределами поля" << endl;
            return false;
        }

        if ((x+y) % 2 != 0) {
            cout << "Фигура может стоять только на черных клетках" << endl;
            return false;
        }

        if (!cells[x][y].isEmpty()) {
            cout << "На клетке уже стоит фигура" << endl;
            return false;
        }

        if ((color==WHITE && y==7 && !isQueen) || (color==BLACK && y==0 && !isQueen)) {
            cout << "На координате "<< char(x + 'A') << char(y + '1') << " должна быть дамка" << endl;
            return false;
        }

        // создаем фигуру нужного типа и ставим на клетку
        Figure* figure;
        if (isQueen) {
            figure = new Queen(color);
        } else {
            figure = new Checker(color);
        }
        cells[x][y].figure = figure;
    }
    return true;
}

void Board::loadFromFile(const std::string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file " << filename << endl;
    }
    if (!loadPieces(file, WHITE)) return;
    if (!loadPieces(file, BLACK)) return;
}

vector<Move> Board::getAllMoves(Color color) {
    vector<Move> result;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Cell& cell = cells[i][j];
            if (cell.figure != nullptr && cell.figure->color == color) {
                vector<Move> pieceMoves = cell.figure->getMoves(*this, &cell);
                result.insert(result.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
    return result;
}

void Board::applyMove(Move &move) {
    if (move.src == move.dst) return;
    // передвигаем фигуру
    move.dst->figure = move.src->figure;
    move.src->figure = nullptr;

    // убираем все срубленные фигуры
    // запоминаем их в move.figures чтобы потом вернуть в undoMove
    move.figures.clear();
    for (int i = 0; i < move.captured.size(); i++) {
        move.figures.push_back(move.captured[i]->figure); // запоминаем
        move.captured[i]->figure = nullptr;
    }

    // проверяем нужно ли превращение в дамку
    move.wasPromotion = needsPromotion(move.dst);
    move.wasPromotion = needsPromotion(move.dst);
    if (move.wasPromotion) {
        promote(move.dst); // превращаем
    }
}

bool Board::needsPromotion(Cell* cell) {
    if (cell->figure == nullptr) return false;
    if (cell->figure->color == WHITE && cell->y == 7) return true; // если белая на 8 ряду, то дамка
    if (cell->figure->color == BLACK && cell->y == 0) return true; // если черная на 1 ряду, то дамка
    return false;
}

void Board::promote(Cell* cell) {
    cell->figure = new Queen(cell->figure->color);
}

void Board::undoMove(Move& move) {
    // если было превращение, то заменяем на Checker
    if (move.wasPromotion) {
        Color color = move.dst->figure->color;
        delete move.dst->figure;
        move.dst->figure = new Checker(color);
    }

    // вернуть фигуру обратно на src
    move.src->figure = move.dst->figure;
    move.dst->figure = nullptr;

    // вернуть срубленные фигуры
    for (int i = 0; i < move.captured.size(); i++) {
        move.captured[i]->figure = move.figures[i];
    }
}

Cell* Board::getCell(int x, int y) {
    return &cells[x][y];
}

bool Board::inBounds(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

bool Board::noFigures(Color color) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (cells[i][j].figure != nullptr &&
                cells[i][j].figure->color == color)
                return false;
    return true;
}