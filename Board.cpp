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

void Board::loadPieces(std::ifstream& file, Color color) {
    std::string label;
    int count;

    // читаем
    file >> label >> count;
    for (int i = 0; i < count; i++) {
        std::string token;
        file >> token;

        // проверка на дамку
        bool isQueen = (token[0] == 'M');
        std::string coord = isQueen ? token.substr(1) : token;

        // получаем x и y путем вычитания из прочтенной строки ASCII начальной координаты (А1)
        int x = coord[0] - 'A';
        int y = coord[1] - '1';

        // создаем фигуру
        Figure* figure;
        if (isQueen) {
            figure = new Queen(color);
        } else {
            figure = new Checker(color);
        }
        cells[x][y].figure = figure; // ставим на клетку
        cout << "Загружена фигура: " << x << " " << y << " цвет: " << color << endl;
    }
}


void Board::loadFromFile(const std::string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file " << filename << endl;
    }
    loadPieces(file, WHITE);
    loadPieces(file, BLACK);
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
    cout << "Ходов найдено для цвета " << color << ": " << result.size() << endl;
    return result;
}

void Board::applyMove(Move &move) {
    // передвигаем фигуру
    move.dst->figure = move.src->figure;
    move.src->figure = nullptr;

    // убираем срубленную фигуру
    if (move.captured != nullptr) {
        move.capturedFigure = move.captured->figure; // запомнили
        move.captured->figure = nullptr;
    }

    // проверяем нужно ли превращение в дамку
    move.wasPromotion = needsPromotion(move.dst);
    if (move.wasPromotion) {
        promote(move.dst); // превращаем
    }
}

bool Board::needsPromotion(Cell* cell) {
    if (cell->figure == nullptr) return false;
    if (cell->figure->color == WHITE && cell->y == 7) return true; // если белая на 7 ряду, то дамка
    if (cell->figure->color == BLACK && cell->y == 0) return true; // если черная на 1 ряду, то дамка
    return false;
}

void Board::promote(Cell* cell) {
    Color color = cell->figure->color; // сохранили цвет шашки
    delete cell->figure; // удалили шашку
    cell->figure = new Queen(color); // создали дамку
}

void Board::undoMove(Move& move) {
    // если было превращение, то вернуть Checker
    if (move.wasPromotion) {
        Color color = move.dst->figure->color;
        delete move.dst->figure;
        move.dst->figure = new Checker(color);
    }

    // вернуть фигуру обратно
    move.src->figure = move.dst->figure;
    move.dst->figure = nullptr;

    // вернуть срубленную фигуру
    if (move.captured != nullptr) {
        move.captured->figure = move.capturedFigure; // вернули на доску
    }
}

bool Board::isWhiteWinning() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (cells[i][j].figure != nullptr &&
                cells[i][j].figure->color == BLACK) {
                bool empty = getAllMoves(BLACK).empty();
                cout << "isWhiteWinning: черные есть, ходов="
                     << getAllMoves(BLACK).size() << endl;
                return empty;
                }
        }
    }
    cout << "isWhiteWinning: черных нет → true" << endl;
    return true;
}

Cell* Board::getCell(int x, int y) {
    return &cells[x][y];
}

bool Board::inBounds(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}