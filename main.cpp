#include <iostream>
#include <locale.h>
#include "Game.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Загрузка позиции..." << endl;
    Game game("task_position.txt", 4);

    cout << "Позиция загружена, запуск решателя:" << endl;
    game.run();

    game.printResult();
    return 0;
}