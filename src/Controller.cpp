#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "Controller.h"

using namespace std;

Controller:: Controller() {}


//leer la entrada
void Controller:: pad(Explorer& explorer, char keybind) {
    //char keybind;
    //cin >> keybind;

    if(explorer.getPlayer() == 1 || flayed == 2){
        switch (keybind){
            case 'w':
                if(flayed == 2) {
                    explorer.moveN(2);
                    flayed = 0;
                } else {
                    explorer.moveN(1);
                }
                break;
            case 'a':
                if(flayed == 2) {
                    explorer.moveW(2);
                    flayed = 0;
                } else {
                    explorer.moveW(1);
                }
                break;
            case 's':
                if(flayed == 2) {
                    explorer.moveS(2);
                    flayed = 0;
                } else {
                    explorer.moveS(1);
                }
                break;
            case 'd':
                if(flayed == 2) {
                    explorer.moveE(2);
                    flayed = 0;
                } else {
                    explorer.moveE(1);
                }
                break;
            default:
                break;
        }
    } else if(explorer.getPlayer() == 2 || flayed == 1) {
        //flechas del teclado aqui
        //char arrowBind;

        // if(keybind == '\033'){
        //     cin >> arrowBind;
        //     cin >> arrowBind;
            switch (keybind){
                case 'G':
                    if(flayed == 1) {
                        explorer.moveN(1);
                        flayed = 0;
                    } else {
                        explorer.moveN(2);
                    }
                    break;
                case 'H':
                    if(flayed == 1) {
                        explorer.moveS(1);
                        flayed = 0;
                    } else {
                        explorer.moveS(2);
                    }
                    break;
                case 'J':
                    if(flayed == 1) {
                        explorer.moveE(1);
                        flayed = 0;
                    } else {
                        explorer.moveE(2);
                    }
                    break;
                case 'K':
                    if(flayed == 1) {
                        explorer.moveW(1);
                        flayed = 0;
                    } else {
                        explorer.moveW(2);
                    }
                    break;
                default:
                    break;
            }
        //}
    }

    if(explorer.getMindFlay(explorer.getPlayer()) == 1){
        if(explorer.getPlayer() == 1){
            cout << endl << "Jugador 1 controla al jugador 2" << endl;
            explorer.setMindFlay(1, 0);
            explorer.setExplorer(2, explorer.getX(2), explorer.getY(2));
            flayed = 2;
            pad(explorer, keybind);
        } else {
            cout << endl << "Jugador 2 controla al jugador 1" << endl;
            explorer.setMindFlay(2, 0);
            explorer.setExplorer(1, explorer.getX(1), explorer.getY(1));
            flayed = 1;
            pad(explorer, keybind);
        }
        //pad(explorer);
        
        return;
    }
    if(explorer.getDoublePlay(explorer.getPlayer()) == 1){
        if(explorer.getPlayer() == 1){
            explorer.deductDoublePlay(1);
            pad(explorer, keybind);
        }else{
            explorer.deductDoublePlay(2);
            pad(explorer, keybind);
        }
    }
}