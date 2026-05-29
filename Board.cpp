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

