#ifndef EXPLORER_H
#define EXPLORER_H

#include <iostream>
#include <vector>
#include "Catacomb.h"


using namespace std;

class Explorer {

    private:
    //player data
    vector<vector<int>> players;

    int player;

    int winner;

    //[1][0] = JUGADOR 1 POSICION EN X
    //[2][1] = JUGADOR 2 POSICION EN Y
    //[1][2] = JUGADOR 1 MOVIMIENTOS DEL PERSONAJE (si tiene 1 es solo él, si tiene 2 es para el rival)
    //[1][3] = JUGADOR 1 SALTOS DISPONIBLES

    Catacomb maze;

    public:
    //instanciando
    Explorer();

    Catacomb& dungeon();
    
    void setExplorer(int p, int x, int y);

    void moveN(int p);

    void moveS(int p);

    void moveE(int p);

    void moveW(int p);

    void moveNE(int p);

    void moveNW(int p);

    void moveSE(int p);

    void moveSW(int p);

    void changePlayer();

    void setWinner(int p);

    void setMindFlay(int p, int status);

    void addJumps(int p);

    void deductJumps(int p);

    int getWinner() const;

    int getPlayer() const;

    int getX(int p) const;

    int getY(int p) const;

    int getMindFlay(int p) const;

    int getJumps(int p) const;

    void thombRaider();
};

#endif