#include "Game.h"
#include "Config.h"

// Función principal del programa
int main() {
    try {
        Game game;
        // Ejemplo de cómo recibir la matriz del backend
        std::vector<std::vector<Node>> initialGrid(MAZE_WIDTH, std::vector<Node>(MAZE_HEIGHT));
        initialGrid[2][2].hasPower1 = true;
        initialGrid[3][3].hasPower2 = true;
        initialGrid[4][3].hasPower3 = true;
        initialGrid[1][1].hasPower4 = true; // Cambiar el poder de [5][5] a [1][1] para ajustarse al nuevo tamaño de la matriz
        initialGrid[0][0].hasPlayer1 = true; // Posicionar al jugador 1 en la celda inicial
        initialGrid[0][1].hasPlayer2 = true; // Posicionar al jugador 2 en la celda final
        game.receiveGrid(initialGrid);
        game.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}







