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

    void addMindFlay(int p);

    void deductMindFlay(int p);

    void addDoublePlay(int p);

    void deductDoublePlay(int p);

    void addJumps(int p);

    void deductJumps(int p);

    int getWinner() const;

    int getPlayer() const;

    int getRival();

    int getX(int p) const;

    int getY(int p) const;

    int getMindFlay(int p) const;

    int getDoublePlay(int p) const;

    int getJumps(int p) const;

    void thombRaider();
};

#endif