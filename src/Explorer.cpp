#include <vector>
#include "Explorer.h"

using namespace std;

Explorer::Explorer() : players(2, vector<int>(5, 0)), player(1), winner(0) {}

Catacomb& Explorer:: dungeon() {
    return maze;
}

void Explorer:: setExplorer(int p, int x, int y){
    players[p - 1][0] = x;
    players[p - 1][1] = y;
}

void Explorer:: moveN(int p){
    // players[p - 1][1]--; //norte

    if(getMindFlay(getPlayer()) != 0){
        deductMindFlay(getPlayer());

    } else if(getDoublePlay(getPlayer()) != 0){
        deductDoublePlay(getPlayer());
    } 

    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];

    if(zone[x][y] && zone[x][y]->getNorth()) {
        players[p - 1][0] = zone[x][y]->getNorth()->getRoom();
        players[p - 1][1] = zone[x][y]->getNorth()->getFloor();

        if(zone[x][y]->getNorth()->getContain() == '$') {

            setWinner(getPlayer());

        } else if(zone[x][y]->getNorth()->getContain() == '@') {

            addMindFlay(getPlayer());
            zone[x][y]->getNorth()->setContain('#');

        } else if(zone[x][y]->getNorth()->getContain() == '&') {

            addJumps(getPlayer());
            zone[x][y]->getNorth()->setContain('#');

        } else if(zone[x][y]->getContain() == '^') {

            zone[x][y]->setNorth(nullptr);
            zone[x][y]->setContain('#');

        }else if(zone[x][y]->getNorth()->getContain() == '%'){

            addDoublePlay(getPlayer());
            zone[x][y]->getNorth()->setContain('#');
        }
        
        if(getMindFlay(1) == 0 && getMindFlay(2) == 0 && getDoublePlay(1) == 0 && getDoublePlay(2) == 0) {
            changePlayer();

        }


    } else {

        if(getMindFlay(getPlayer()) == 1 && getJumps(getRival()) > 0 && zone[x][y]->getContain() != '^' && zone[x - 1][y]){

            --players[getRival()-1][0];

            if(zone[x-1][y]->getContain() == '$' && zone[x-1][y]){ //in case of wall jumping over treasure
                setWinner(getRival());

            } else if(zone[x-1][y]->getContain() == '&' && zone[x-1][y]){
                addJumps(getRival());
                zone[x-1][y]->setContain('#');

            } else if(zone[x-1][y]->getContain() == '%' && zone[x-1][y]){
                addDoublePlay(getRival());
                zone[x-1][y]->setContain('#');
            }

            deductJumps(getRival());
        
        } else if(getJumps(getPlayer()) > 0 && zone[x][y]->getContain() != '^' && zone[x - 1][y]) {
            --players[p - 1][0];

            if(zone[x-1][y]->getContain() == '$' && zone[x-1][y]){ //in case of wall jumping over treasure
                setWinner(getPlayer());

            } else if(zone[x-1][y]->getContain() == '@' && zone[x-1][y]){
                addMindFlay(getPlayer());
                zone[x-1][y]->setContain('#');

            } else if(zone[x-1][y]->getContain() == '&' && zone[x-1][y]){
                addJumps(getPlayer());
                zone[x-1][y]->setContain('#');

            } else if(zone[x-1][y]->getContain() == '%' && zone[x-1][y]){
                addDoublePlay(getPlayer());
                zone[x-1][y]->setContain('#');
            }

            deductJumps(getPlayer());

            if(getMindFlay(1) == 0 && getMindFlay(2) == 0 && getDoublePlay(1) == 0 && getDoublePlay(2) == 0){
                changePlayer();
            }
            
        } else {
            cout << endl << "Sergio's words echoed... 'There's a time and place for everything but not now!'" << endl;
        }
    }
}

void Explorer:: moveS(int p){

    if(getMindFlay(getPlayer()) != 0){
        deductMindFlay(getPlayer());

    } else if(getDoublePlay(getPlayer()) != 0){
        deductDoublePlay(getPlayer());
    }

    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];

    if(zone[x][y] && zone[x][y]->getSouth()) {
        players[p - 1][0] = zone[x][y]->getSouth()->getRoom();
        players[p - 1][1] = zone[x][y]->getSouth()->getFloor();

        if(zone[x][y]->getSouth()->getContain() == '$') {

            setWinner(getPlayer());

        } else if(zone[x][y]->getSouth()->getContain() == '@') {

            addMindFlay(getPlayer());
            zone[x][y]->getSouth()->setContain('#');

        } else if(zone[x][y]->getSouth()->getContain() == '&') {

            addJumps(getPlayer());
            zone[x][y]->getSouth()->setContain('#');

        } else if(zone[x][y]->getContain() == 'v') {

            zone[x][y]->setSouth(nullptr);
            zone[x][y]->setContain('#');

        } else if(zone[x][y]->getSouth()->getContain() == '%'){

            addDoublePlay(getPlayer());
            zone[x][y]->getSouth()->setContain('#');
        }

        if(getMindFlay(1) == 0 && getMindFlay(2) == 0 && getDoublePlay(1) == 0 && getDoublePlay(2) == 0) {
            changePlayer();

        }

    } else {

        if(getMindFlay(getPlayer()) == 1 && getJumps(getRival()) > 0 && zone[x][y]->getContain() != 'v' && zone[x + 1][y]){
            
             --players[getRival()-1][0];

            if(zone[x+1][y]->getContain() == '$' && zone[x+1][y]){ //in case of wall jumping over treasure
                setWinner(getRival());

            } else if(zone[x+1][y]->getContain() == '&' && zone[x+1][y]){
                addJumps(getRival());
                zone[x+1][y]->setContain('#');

            } else if(zone[x+1][y]->getContain() == '%' && zone[x+1][y]){
                addDoublePlay(getRival());
                zone[x+1][y]->setContain('#');
            }

            deductJumps(getRival());
        
        } else if(getJumps(getPlayer()) > 0 && zone[x][y]->getContain() != 'v' && zone[x + 1][y]) {
            ++players[p - 1][0];

            if(zone[x+1][y]->getContain() == '$' && zone[x+1][y]){
                setWinner(getPlayer());

            } else if(zone[x+1][y]->getContain() == '@' && zone[x+1][y]){
                addMindFlay(getPlayer());
                zone[x+1][y]->setContain('#');

            } else if(zone[x+1][y]->getContain() == '&' && zone[x+1][y]){
                addJumps(getPlayer());
                zone[x+1][y]->setContain('#');

            } else if(zone[x+1][y]->getContain() == '%' && zone[x+1][y]){
                addDoublePlay(getPlayer());
                zone[x+1][y]->setContain('#');
            }

            deductJumps(getPlayer());

            if(getMindFlay(1) == 0 && getMindFlay(2) == 0 && getDoublePlay(1) == 0 && getDoublePlay(2) == 0){
                changePlayer();
            }
        } else {
            cout << endl << "Sergio's words echoed... 'There's a time and place for everything but not now!'" << endl;
        }
    }

}

void Explorer:: moveE(int p){

    if(getMindFlay(getPlayer()) != 0){
        deductMindFlay(getPlayer());

    } else if(getDoublePlay(getPlayer()) != 0){
        deductDoublePlay(getPlayer());
    } 

    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];
    
    if(zone[x][y] && zone[x][y]->getEast()) {
        players[p - 1][0] = zone[x][y]->getEast()->getRoom();
        players[p - 1][1] = zone[x][y]->getEast()->getFloor();

        if(zone[x][y]->getEast()->getContain() == '$') {

            setWinner(getPlayer());

        } else if(zone[x][y]->getEast()->getContain() == '@') {

            addMindFlay(getPlayer());
            zone[x][y]->getEast()->setContain('#');

        } else if(zone[x][y]->getEast()->getContain() == '&') {

            addJumps(getPlayer());
            zone[x][y]->getEast()->setContain('#');

        } else if(zone[x][y]->getContain() == '>') {

            zone[x][y]->setEast(nullptr);
            zone[x][y]->setContain('#');

        } else if(zone[x][y]->getEast()->getContain() == '%'){

            addDoublePlay(getPlayer());
            zone[x][y]->getEast()->setContain('#');
        }

        if(getMindFlay(1) == 0 && getMindFlay(2) == 0 && getDoublePlay(1) == 0 && getDoublePlay(2) == 0) {
            changePlayer();

        }

    } else {

        if(getMindFlay(getPlayer()) == 1 && getJumps(getRival()) > 0 && zone[x][y]->getContain() != '>' && zone[x][y+1]){

            --players[getRival()-1][0];

            if(zone[x][y+1]->getContain() == '$' && zone[x][y+1]){ //in case of wall jumping over treasure
                setWinner(getRival());

            } else if(zone[x][y+1]->getContain() == '&' && zone[x][y+1]){
                addJumps(getRival());
                zone[x][y+1]->setContain('#');

            } else if(zone[x][y+1]->getContain() == '%' && zone[x][y+1]){
                addDoublePlay(getRival());
                zone[x][y+1]->setContain('#');
            }

            deductJumps(getRival());
        
        } else if(getJumps(getPlayer()) > 0 && zone[x][y]->getContain() != '>' && zone[x ][y + 1]) {
            ++players[p - 1][1];

            if(zone[x][y+1]->getContain() == '$' && zone[x][y+1]){
                setWinner(getPlayer());

            } else if(zone[x][y+1]->getContain() == '@' && zone[x][y+1]){
                addMindFlay(getPlayer());
                zone[x][y+1]->setContain('#');

            } else if(zone[x][y+1]->getContain() == '&' && zone[x][y+1]){
                addJumps(getPlayer());
                zone[x][y+1]->setContain('#');

            } else if(zone[x][y+1]->getContain() == '%' && zone[x][y+1]){
                addDoublePlay(getPlayer());
                zone[x][y+1]->setContain('#');
            }

            deductJumps(getPlayer());

            if(getMindFlay(1) == 0 && getMindFlay(2) == 0 && getDoublePlay(1) == 0 && getDoublePlay(2) == 0){
                changePlayer();
            }

        } else {
            cout << endl << "Sergio's words echoed... 'There's a time and place for everything but not now!'" << endl;
        }
    }
}

void Explorer:: moveW(int p){

    if(getMindFlay(getPlayer()) != 0){
        deductMindFlay(getPlayer());

    } else if(getDoublePlay(getPlayer()) != 0){
        deductDoublePlay(getPlayer());
    } 

    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];

    if(zone[x][y] && zone[x][y]->getWest()) {
        players[p - 1][0] = zone[x][y]->getWest()->getRoom();
        players[p - 1][1] = zone[x][y]->getWest()->getFloor();

        if(zone[x][y]->getWest()->getContain() == '$') {
            
            setWinner(getPlayer());
            
        } else if(zone[x][y]->getWest()->getContain() == '@') {

            addMindFlay(getPlayer());
            zone[x][y]->getWest()->setContain('#');

        } else if(zone[x][y]->getWest()->getContain() == '&') {

            addJumps(getPlayer());
            zone[x][y]->getWest()->setContain('#');

        } else if(zone[x][y]->getContain() == '<') {

            zone[x][y]->setWest(nullptr);
            zone[x][y]->setContain('#');

        } else if(zone[x][y]->getWest()->getContain() == '%'){

            addDoublePlay(getPlayer());
            zone[x][y]->getWest()->setContain('#');
        }

        if(getMindFlay(1) == 0 && getMindFlay(2) == 0 && getDoublePlay(1) == 0 && getDoublePlay(2) == 0) {
            changePlayer();

        }

    } else {

        if(getMindFlay(getPlayer()) == 1 && getJumps(getRival()) > 0 && zone[x][y]->getContain() != '<' && zone[x][y-1]){

            --players[getRival()-1][0];

            if(zone[x][y-1]->getContain() == '$' && zone[x][y-1]){ //in case of wall jumping over treasure
                setWinner(getRival());

            } else if(zone[x][y-1]->getContain() == '&' && zone[x][y-1]){
                addJumps(getRival());
                zone[x][y-1]->setContain('#');

            } else if(zone[x][y-1]->getContain() == '%' && zone[x][y-1]){
                addDoublePlay(getRival());
                zone[x][y-1]->setContain('#');
            }

            deductJumps(getRival());
        
        } else if(getJumps(getPlayer()) > 0 && zone[x][y]->getContain() != '<' && zone[x ][y - 1]) {
            --players[p - 1][1];

            if(zone[x][y-1]->getContain() == '$' && zone[x][y-1]){
                setWinner(getPlayer());

            } else if(zone[x][y-1]->getContain() == '@' && zone[x][y-1]){
                addMindFlay(getPlayer());
                zone[x][y-1]->setContain('#');

            } else if(zone[x][y-1]->getContain() == '&' && zone[x][y-1]){
                addJumps(getPlayer());
                zone[x][y-1]->setContain('#');

            } else if(zone[x][y-1]->getContain() == '%' && zone[x][y-1]){
                addDoublePlay(getPlayer());
                zone[x][y-1]->setContain('#');
            }

            deductJumps(getPlayer());

            if(getMindFlay(1) == 0 && getMindFlay(2) == 0 && getDoublePlay(1) == 0 && getDoublePlay(2) == 0){
                changePlayer();
            }

        } else {
            cout << endl << "Sergio's words echoed... 'There's a time and place for everything but not now!'" << endl;
        }
    }
}

void Explorer:: moveNE(int p){
    //players[p - 1][0]++;
    //players[p - 1][1]--;
    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];
    
    
}

void Explorer:: moveNW(int p){
    //players[p - 1][0]--;
    //players[p - 1][1]--;
    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];
    
}

void Explorer:: moveSE(int p){
    //players[p - 1][0]++;
    //players[p - 1][1]++;
    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];
    
}

void Explorer:: moveSW(int p){
    //players[p - 1][0]--;
    //players[p - 1][1]++;
    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];
    
}

void Explorer:: changePlayer(){
    if(getPlayer() == 1) {
        player = 2;
    } else {
        player = 1;
    }
}

int Explorer:: getRival(){
    if(getPlayer() == 1) {
        return 2;
    } else {
        return 1;
    }
}

void Explorer:: setWinner(int p){
    winner = p;
}

void Explorer:: addMindFlay(int p){
    players[p - 1][2] += 2;
}

void Explorer:: deductMindFlay(int p){
    players[p - 1][2]--;
}

void Explorer:: addDoublePlay(int p){
    players[p - 1][4]++;
}

void Explorer:: deductDoublePlay(int p){
    players[p - 1][4]--;
}

void Explorer:: addJumps(int p){
    players[p - 1][3]++;
}

void Explorer:: deductJumps(int p){
    players[p - 1][3]--;
}

int Explorer:: getWinner() const{
    return winner;
}

int Explorer:: getPlayer() const {
    return player;
}

int Explorer:: getX(int p) const {
    return players[p - 1][0];
}

int Explorer::getY(int p) const {
    return players[p - 1][1];
}

int Explorer::getMindFlay(int p) const {
    return players[p - 1][2];
}

int Explorer:: getDoublePlay(int p) const{
    return players[p - 1][4];
}

int Explorer::getJumps(int p) const {
    return players[p - 1][3];
}


//para visualizar en terminal
// void Explorer:: thombRaider() {

//     auto& zone = dungeon().mapped();

//     int row = zone.size() * 2 + 1;
//     int col = zone[0].size() * 2 + 1;
//     vector<vector<char>> thomb(row, vector<char>(col, ' '));

//     for(int r = 0; r < zone.size(); ++r){
//         for(int c = 0; c < zone[0].size(); ++c){
//             int rr = r * 2 + 1;
//             int cc = c * 2 + 1;

//             if(zone[r][c] == nullptr){
//                 thomb[rr][cc] = ' ';
//             } else {
//                 thomb[rr][cc] = zone[r][c]->getContain();

//                 if(zone[r][c]->getRoom() == getX(1) && zone[r][c]->getFloor() == getY(1) && zone[r][c] != nullptr) {
//                     thomb[rr][cc] = '1';
//                 } else if(zone[r][c]->getRoom() == getX(2) && zone[r][c]->getFloor() == getY(2) && zone[r][c] != nullptr) {
//                     thomb[rr][cc] = '2';
//                 }

//                 if(zone[r][c] != nullptr) {
//                     if(zone[r][c]->getEast() != nullptr && zone[r][c]->getContain() != '>') {
//                         thomb[rr][cc + 1] = '-';
//                     }
//                     if(zone[r][c]->getSouth() != nullptr && zone[r][c]->getContain() != 'v') {
//                         thomb[rr + 1][cc] = '|';
//                     }
//                     if(zone[r][c]->getWest() != nullptr && zone[r][c]->getContain() != '<') {
//                         thomb[rr][cc - 1] = '-';
//                     }
//                     if(zone[r][c]->getNorth() != nullptr && zone[r][c]->getContain() != '^') {
//                         thomb[rr - 1][cc] = '|';
//                     }
//                 }
//             }
//         }
//     }

//     for (int r = 0; r < row; ++r) {
//         for (int c = 0; c < col; ++c) {
//             cout << thomb[r][c] << " ";
//         }
//         cout << endl;
//     }
// }