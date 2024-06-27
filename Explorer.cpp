#include <vector>
#include "Explorer.h"

using namespace std;

Explorer::Explorer() : players(2, vector<int>(4, 0)), player(1) {}

//[1][0] = JUGADOR 1 POSICION EN X
//[2][1] = JUGADOR 2 POSICION EN Y
//[1][2] = JUGADOR 1 MOVIMIENTOS DEL PERSONAJE (si tiene 1 es solo él, si tiene 2 es para el rival)
//[1][3] = JUGADOR 1 SALTOS DISPONIBLES

Catacomb& Explorer:: dungeon() {
    return maze;
}

void Explorer:: setExplorer(int p, int x, int y){
    players[p - 1][0] = x;
    players[p - 1][1] = y;
}

void Explorer:: moveN(int p){
    //players[p - 1][1]--; //norte
    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];
    Chunk* tile = zone[x][y];

    if(tile && tile->getNorth()) {
        Chunk* tileN = tile->getNorth();
        players[p - 1][0] = tileN->getFloor();
        players[p - 1][1] = tileN->getRoom();
    }
}

void Explorer:: moveS(int p){
    //players[p - 1][1]++; //sur
    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];
    Chunk* tile = zone[x][y];

    if(tile && tile->getSouth()) {
        Chunk* tileS = tile->getSouth();
        players[p - 1][0] = tileS->getFloor();
        players[p - 1][1] = tileS->getRoom();
    }
}

void Explorer:: moveE(int p){
    //players[p - 1][0]++; //este
    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];
    Chunk* tile = zone[x][y];

    if(tile && tile->getEast()) {
        Chunk* tileE = tile->getEast();
        players[p - 1][0] = tileE->getFloor();
        players[p - 1][1] = tileE->getRoom();
    }
}

void Explorer:: moveW(int p){
    //players[p - 1][0]--; //oeste
    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];
    Chunk* tile = zone[x][y];

    if(tile && tile->getWest()) {
        Chunk* tileW = tile->getWest();
        players[p - 1][0] = tileW->getFloor();
        players[p - 1][1] = tileW->getRoom();
    }
}

void Explorer:: moveNE(int p){
    //players[p - 1][0]++;
    //players[p - 1][1]--;
    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];
    Chunk* tile = zone[x][y];

    if(tile && tile->getNorthEast()) {
        Chunk* tileNE = tile->getNorthEast();
        players[p - 1][0] = tileNE->getFloor();
        players[p - 1][1] = tileNE->getRoom();
    }
}

void Explorer:: moveNW(int p){
    //players[p - 1][0]--;
    //players[p - 1][1]--;
    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];
    Chunk* tile = zone[x][y];

    if(tile && tile->getNorthWest()) {
        Chunk* tileNW = tile->getNorthWest();
        players[p - 1][0] = tileNW->getFloor();
        players[p - 1][1] = tileNW->getRoom();
    }
}

void Explorer:: moveSE(int p){
    //players[p - 1][0]++;
    //players[p - 1][1]++;
    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];
    Chunk* tile = zone[x][y];

    if(tile && tile->getSouthEast()) {
        Chunk* tileSE = tile->getSouthEast();
        players[p - 1][0] = tileSE->getFloor();
        players[p - 1][1] = tileSE->getRoom();
    }
}

void Explorer:: moveSW(int p){
    //players[p - 1][0]--;
    //players[p - 1][1]++;
    auto& zone = dungeon().mapped();

    int x = players[p - 1][0];
    int y = players[p - 1][1];
    Chunk* tile = zone[x][y];

    if(tile && tile->getSouthWest()) {
        Chunk* tileSW = tile->getSouthWest();
        players[p - 1][0] = tileSW->getFloor();
        players[p - 1][1] = tileSW->getRoom();
    }
}

void Explorer:: changePlayer(int p){
    player = p;
}

void Explorer:: setMindFlay(int p, int status){
    players[p - 1][2] = status;
}

void Explorer:: addJumps(int p){
    players[p - 1][3]++;
}

void Explorer:: deductJumps(int p){
    players[p - 1][3]--;
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

int Explorer::getJumps(int p) const {
    return players[p - 1][3];
}



void Explorer:: thombRaider() {

    auto& zone = dungeon().mapped();

    //cout << endl << "Parte1 sirve" << endl;

    // //metodo para visualizar los indicadores numericos de los nodos
    // for(int room = 0; room < zone.size(); ++room){
    //     for(int floor = 0; floor < zone[room].size(); ++floor){
    //         if(zone[room][floor] != nullptr) {
    //             cout << "[" << zone[room][floor]->getRoom() << ", " << zone[room][floor]->getFloor() << "]";
    //         } else {
    //             cout << "      ";
    //         }
    //         cout << " ";
    //     }
    //     cout << endl;
    // }

    int row = zone.size() * 2 + 1;
    int col = zone[0].size() * 2 + 1;
    vector<vector<char>> thomb(row, vector<char>(col, ' '));

    for(int r = 0; r < zone.size(); ++r){
        for(int c = 0; c < zone[0].size(); ++c){
            int rr = r * 2 + 1;
            int cc = c * 2 + 1;

            if(zone[r][c] == nullptr){
                thomb[rr][cc] = ' ';
            } else {
                thomb[rr][cc] = zone[r][c]->getContain();

                if(zone[r][c]->getFloor() == getX(1) && zone[r][c]->getRoom() == getY(1) && zone[r][c] != nullptr) {
                    thomb[rr][cc] = '1';
                } else if(zone[r][c]->getFloor() == getX(2) && zone[r][c]->getRoom() == getY(2) && zone[r][c] != nullptr) {
                    thomb[rr][cc] = '2';
                }

                if(zone[r][c] != nullptr) {
                    if(zone[r][c]->getEast() != nullptr) {
                        thomb[rr][cc + 1] = '-';
                    }
                    if(zone[r][c]->getSouth() != nullptr) {
                        thomb[rr + 1][cc] = '|';
                    }
                    if(zone[r][c]->getWest() != nullptr) {
                        thomb[rr][cc - 1] = '-';
                    }
                    if(zone[r][c]->getNorth() != nullptr) {
                        thomb[rr - 1][cc] = '|';
                    }
                }
            }
        }
    }

    for (int r = 0; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            cout << thomb[r][c] << " ";
        }
        cout << endl;
    }
}