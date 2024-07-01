#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "Controller.h"

using namespace std;

Controller:: Controller() {}


//leer la entrada
void Controller:: pad(Explorer& explorer, char keybind) {

    if(explorer.getPlayer() == 1){
        switch (keybind){
            case 'w':
                if(explorer.getMindFlay(1) > 1) {
                    explorer.moveN(2);
                    break;

                } else {
                    explorer.moveN(1);
                }
                break;
            case 'a':
                if(explorer.getMindFlay(1) > 1) {
                    explorer.moveW(2);
                    break;

                } else {
                    explorer.moveW(1);
                }
                break;
            case 's':
                if(explorer.getMindFlay(1) > 1) {
                    explorer.moveS(2);
                    break;
                } else {
                    explorer.moveS(1);
                }
                break;
            case 'd':
                if(explorer.getMindFlay(1) > 1) {
                    explorer.moveE(2);
                    break;
                } else {
                    explorer.moveE(1);
                }
                break;
            default:
                break;
        }
    } else if(explorer.getPlayer() == 2) {

            //flechas del teclado aqui
            switch (keybind){
                case 'I':
                    if(explorer.getMindFlay(2) > 1) {
                        explorer.moveN(1);
                        break;

                    } else {
                        explorer.moveN(2);
                    }
                    break;
                case 'K':
                    if(explorer.getMindFlay(2) > 1) {
                        explorer.moveS(1);
                        break;

                    } else {
                        explorer.moveS(2);
                    }
                    break;
                case 'L':
                    if(explorer.getMindFlay(2) > 1) {
                        explorer.moveE(1);
                        break;
                    } else {
                        explorer.moveE(2);
                    }
                    break;
                case 'J':
                    if(explorer.getMindFlay(2) > 1) {
                        explorer.moveW(1);
                        break;
                    } else {
                        explorer.moveW(2);
                    }
                    break;
                default:
                    break;
            }
    }
}