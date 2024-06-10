#include "Explorer.h"

using namespace std;

Explorer::Explorer() : players(2, vector<int>(4, 0)) {}

        //[1][0] = JUGADOR 1 POSICION EN X
        //[2][1] = JUGADOR 2 POSICION EN Y
        //[1][2] = JUGADOR 1 MOVIMIENTOS DEL PERSONAJE (si tiene 1 es solo él, si tiene 2 es para el rival)
        //[1][3] = JUGADOR 1 SALTOS DISPONIBLES

void Explorer:: setExplorer(int p, int x, int y){
    players[p - 1][0] = x;
    players[p - 1][1] = y;
}

void Explorer:: moveN(int p){
    players[p - 1][1]++;
}

void Explorer:: moveS(int p){
    players[p - 1][1]--;
}

void Explorer:: moveE(int p){
    players[p - 1][0]++;
}

void Explorer:: moveW(int p){
    players[p - 1][0]--;
}

void Explorer:: moveNE(int p){
    players[p - 1][0]++;
    players[p - 1][1]++;
}

void Explorer:: moveNW(int p){
    players[p - 1][0]--;
    players[p - 1][1]++;
}

void Explorer:: moveSE(int p){
    players[p - 1][0]++;
    players[p - 1][1]--;
}

void Explorer:: moveSW(int p){
    players[p - 1][0]--;
    players[p - 1][1]--;
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