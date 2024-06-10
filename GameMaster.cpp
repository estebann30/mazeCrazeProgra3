//main.cpp por ahora

#include <iostream>
#include "Explorer.h"
#include "Controls.h"
#include "Dungeon.h"


using namespace std;

int main() {
    Dungeon maze;
    Explorer explorer;

    maze.mazeMapping(5, 5);
    maze.tester();

    explorer.setExplorer(1, 0 , 0);
    explorer.setExplorer(2, 0, 1);

    explorer.changePlayer(1);

    Controls controller;
    controller.pad(explorer);


    int p1x = explorer.getX(1);

    cout << "La posicion en X del explorador 1 es: " << p1x << endl;

    //cout << "Hola" << endl;

    return 0;
}