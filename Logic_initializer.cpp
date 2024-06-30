#include "Logic_initializer.h"
#include <iostream>

using namespace std;

void Logic_initializer::initialize() {

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
}

