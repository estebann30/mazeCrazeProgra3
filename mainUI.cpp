#include "Game.h"
#include "Config.h"
#include "WindowSizeException.h"
#include "MenuUI.hpp"

int main() {
    try {
        Game game;
        //Menu menu();
        std::vector<std::vector<Node>> initialGrid(MAZE_WIDTH, std::vector<Node>(MAZE_HEIGHT));
        initialGrid[2][2].hasPower1 = true;
        initialGrid[3][3].hasPower2 = true;
        initialGrid[4][3].hasPower3 = true;
        initialGrid[1][1].hasPower4 = true; 
        initialGrid[0][0].hasPlayer1 = true; 
        initialGrid[0][1].hasPlayer2 = true; 
        initialGrid[0][2].treasure1 = true;
        game.receiveGrid(initialGrid);

        game.run();
        
        
    } catch (const WindowSizeException& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}