#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "Controller.h"

using namespace std;

Controller:: Controller() {}


//leer la entrada
void Controller:: pad(Catacomb& maze) {
    char keybind;

    cin >> keybind;
    //keybind = 'w';

    if(maze.explorers().getPlayer() == 1){
        switch (keybind){
            case 'w':
            case 'W':
                maze.explorers().moveN(1);
                break;
            case 'a':
            case 'A':
                maze.explorers().moveW(1);
                break;
            case 's':
            case 'S':
                maze.explorers().moveS(1);
                break;
            case 'd':
            case 'D':
                maze.explorers().moveE(1);
                break;
            default:
                break;
        }
    } else if(maze.explorers().getPlayer() == 2) {
        
        //flechas del teclado aqui
        char arrowBind;

        if(keybind == '\033'){
            cin >> arrowBind;
            cin >> arrowBind;
            switch (arrowBind){
                case 'A':
                    maze.explorers().moveN(maze.explorers().getPlayer());
                    break;
                case 'B':
                    maze.explorers().moveS(maze.explorers().getPlayer());
                    break;
                case 'C':
                    maze.explorers().moveE(maze.explorers().getPlayer());
                    break;
                case 'D':
                    maze.explorers().moveW(maze.explorers().getPlayer());
                    break;
                default:
                    break;
            }
        }
    }

    if(maze.explorers().getMindFlay(maze.explorers().getPlayer()) == 1){
        if(maze.explorers().getPlayer() == 1){
            maze.explorers().setMindFlay(1, 0);
            maze.explorers().setExplorer(2, maze.explorers().getX(2), maze.explorers().getY(2));
            
        } else {
            maze.explorers().setMindFlay(2, 0);
            maze.explorers().setExplorer(1, maze.explorers().getX(1), maze.explorers().getY(1));
        }
        pad(maze);
        return;
    }
}