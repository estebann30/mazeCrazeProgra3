#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "Explorer.h"
#include "Controls.h"

using namespace std;

Controls:: Controls() {}

//leer la entrada
void Controls:: pad(Explorer& explorer) {
    char keybind;

    cin >> keybind;
    //keybind = 'w';

    if(explorer.getPlayer() == 1) {
        switch (keybind){
            case 'w':
            case 'W':
                explorer.moveN(explorer.getPlayer());
                break;
            case 'a':
            case 'A':
                explorer.moveW(explorer.getPlayer());
                break;
            case 's':
            case 'S':
                explorer.moveS(explorer.getPlayer());
                break;
            case 'd':
            case 'D':
                explorer.moveE(explorer.getPlayer());
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
                    explorer.moveN(explorer.getPlayer());
                    break;
                case 'B':
                    explorer.moveS(explorer.getPlayer());
                    break;
                case 'C':
                    explorer.moveW(explorer.getPlayer());
                    break;
                case 'D':
                    explorer.moveE(explorer.getPlayer());
                    break;
                default:
                    break;
            }
        }
    }

    if(explorer.getMindFlay(explorer.getPlayer()) == 1){
        if(explorer.getPlayer() == 1){
            explorer.setExplorer(2, explorer.getX(2), explorer.getY(2));
            explorer.setMindFlay(explorer.getPlayer(), 0);
        } else {
            explorer.setExplorer(1, explorer.getX(1), explorer.getY(1));
            explorer.setMindFlay(explorer.getPlayer(), 0);
        }
        pad(explorer);
        return;
    }


}  


// int main(){
//     Controls keyPad;

//     char key = keyPad.pad(1);

//     cout << "Presionaste la tecla: " << key << "\n";

//     return 0;
// }