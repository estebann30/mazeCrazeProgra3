//for UI
#include "Game.h"
#include "Config.h"
#include "WindowSizeException.h"
#include "MenuUI.hpp"
#include <SFML/Graphics.hpp>

//for Logic
#include "Controller.h"
#include "Explorer.h"

#include <iostream>
using namespace std;

int main(){

    Explorer explorer;
    //Controller control;


    explorer.dungeon().mazeMapping(); //crea la matriz

    explorer.setExplorer(1, 0, 0);  
    explorer.setExplorer(2, MAZE_WIDTH-1, MAZE_HEIGHT-1);

    explorer.dungeon().tunneler(); //le añade portales, poderes, conexiones (tambien quita conexiones)

    //explorer.thombRaider(); //visualizar en terminal


    try {
        Game game(explorer);
        //Menu menu();

        game.run(explorer);
        
        
    } catch (const WindowSizeException& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    

    

    return 0;
}