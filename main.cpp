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
    explorer.dungeon().tunneler();

    explorer.setExplorer(1, 0, 0);
    explorer.setExplorer(2, 4, 4);

    explorer.changePlayer(1);

    explorer.thombRaider();

    //control.pad(explorer);

    //explorer.thombRaider();


    int turns = 4;

    while(turns > 0) {

        cout << endl << "luego del cambio:" << endl;

        control.pad(explorer);

        if(explorer.getPlayer() == 1) {
            explorer.changePlayer(2);
        } else {
            explorer.changePlayer(1);
        }
        
        explorer.thombRaider();

        --turns;
    }

    return 0;
}