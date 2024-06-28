#ifndef CATACOMB_H
#define CATACOMB_H

#include <vector>
#include "Chunk.h"

using namespace std;

class Catacomb {
    private:
    vector<vector<Chunk*>> layout;

    bool checking;

    void DFS(int p1x, int p1y, int p2x, int p2y, int room, int floor);
    void BFS();

    public:
    Catacomb();
    vector<vector<Chunk*>>& mapped();

    void mazeMapping();
    void tunneler();
};

#endif