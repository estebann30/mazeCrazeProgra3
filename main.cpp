#include <iostream>
#include "Controller.h"
#include "Explorer.h"

//#include "Catacomb.h"
//#include "Dungeon.h"

using namespace std;

int main() {
    //cout << endl << "Hola" << endl;


    Explorer explorer;
    Controller control;


    explorer.dungeon().mazeMapping();

    explorer.setExplorer(1, 0, 0);
    explorer.setExplorer(2, 6, 6);

    explorer.dungeon().tunneler();

    explorer.thombRaider();

    while(explorer.getWinner() == 0) {

        cout << endl << "Turno del jugador: " << explorer.getPlayer() << endl;

        control.pad(explorer);

        explorer.thombRaider();

    }

    cout << endl << "el ganador es el jugador: " << explorer.getWinner() << endl;


    return 0;
}

