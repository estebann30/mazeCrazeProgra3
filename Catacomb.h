#ifndef CATACOMB_H
#define CATACOMB_H

#include "Chunk.h"
#include "Explorer.h"
#include <vector>

using namespace std;

class Catacomb {
    private:
    vector<vector<Chunk*>> layout;
    Explorer explorer;

    void DFS(int p1x, int p1y, int p2x, int p2y, int room, int floor);
    void BFS();

    public:
    Catacomb();
    Explorer& explorers();
    void mazeMapping(int rows, int cols);
    void test();

    void thombRaider();
};

#endif