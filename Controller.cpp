#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "Controller.h"

using namespace std;

Controller:: Controller() {}


//leer la entrada
void Controller:: pad(Explorer& explorer) {
    char keybind;

    cin >> keybind;
    //keybind = 'w';

    if(explorer.getPlayer() == 1){
        switch (keybind){
            case 'w':
            case 'W':
                explorer.moveN(1);
                break;
            case 'a':
            case 'A':
                explorer.moveW(1);
                break;
            case 's':
            case 'S':
                explorer.moveS(1);
                break;
            case 'd':
            case 'D':
                explorer.moveE(1);
                break;
            default:
                break;
        }
    } else if(explorer.getPlayer() == 2) {
        
        //flechas del teclado aqui
        char arrowBind;

        if(keybind == '\033'){
            cin >> arrowBind;
            cin >> arrowBind;
            switch (arrowBind){
                case 'A':
                    explorer.moveN(2);
                    break;
                case 'B':
                    explorer.moveS(2);
                    break;
                case 'C':
                    explorer.moveE(2);
                    break;
                case 'D':
                    explorer.moveW(2);
                    break;
                default:
                    break;
            }
        }
    }

    if(explorer.getMindFlay(explorer.getPlayer()) == 1){
        if(explorer.getPlayer() == 1){
            explorer.setMindFlay(1, 0);
            explorer.setExplorer(2, explorer.getX(2), explorer.getY(2));
            
        } else {
            explorer.setMindFlay(2, 0);
            explorer.setExplorer(1, explorer.getX(1), explorer.getY(1));
        }
        pad(explorer);
        return;
    }
}