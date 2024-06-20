#include <iostream>
#include "Controller.h"
#include "Catacomb.h"

//#include "Dungeon.h"

using namespace std;

int main() {
    // Dungeon maze;
    // Controller control;
    
    // int sizeX = 9;
    // int sizeY = 7;


    // maze.mazeMapping(sizeX, sizeY);

    // maze.explorers().setExplorer(1, 0, 0);
    // maze.explorers().setExplorer(2, sizeX, sizeY);

    // maze.tester();

    // cout << endl << "luego del cambio:" << endl;

    // control.pad(maze);

    // maze.tester();


    //cout << endl << "Hola" << endl;
    

    Catacomb maze;
    Controller control;

    int sizeX = 5;
    int sizeY = 5;

    // Inicializar el laberinto
    maze.mazeMapping(sizeX, sizeY);

    //Jugadores
    maze.explorers().setExplorer(1, 0, 0);
    maze.explorers().setExplorer(2, sizeX - 1, sizeY - 1);

    // Imprimir el laberinto antes de los cambios
    cout << "Laberinto con caminos hechos:" << endl;
    //maze.test();
    maze.thombRaider();

    int turns = 4;

    while(turns > 0) {

        cout << endl << "luego del cambio:" << endl;

        control.pad(maze);

        if(maze.explorers().getPlayer() == 1) {
            maze.explorers().changePlayer(2);
        } else {
            maze.explorers().changePlayer(1);
        }
        
        maze.thombRaider();

        --turns;
    }

    

    return 0;
}