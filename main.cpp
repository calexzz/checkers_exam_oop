#include <iostream>
#include <locale.h>
#include "Game.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Загрузка позиции..." << endl;
    Game game("task_position.txt", 4); // создаём игру: загружаем позицию из файла

    game.run(); // запускаем решатель

    game.printResult(); // выводим результат
    return 0;
}