#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include "Chunk.h"

using namespace std;

class Dungeon {
private:
    vector<vector<Chunk>> layout;

public:
    Dungeon();

    void mazeMapping(int rows, int cols);
    void tester();
};

#endif
