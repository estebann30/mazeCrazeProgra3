#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <queue>
#include <algorithm>
#include "Catacomb.h"

using namespace std;

Catacomb:: Catacomb() {}

void Catacomb:: mazeMapping() {
    int rooms = MAZE_WIDTH;
    int floors = MAZE_HEIGHT;
    
    checking = true;

    while(checking) {
        layout = vector<vector<Chunk*>>(rooms, vector<Chunk*>(floors, nullptr));
        DFS(0, 0, rooms -1, floors -1, rooms, floors);
        //BFS(0, 0, rooms -1, floors -1, rooms, floors);
    }
}

vector<vector<Chunk*>>& Catacomb:: mapped() {
    return layout;
}

void Catacomb::DFS(int p1x, int p1y, int p2x, int p2y, int rows, int cols) {
    stack<pair<int, int>> layer;
    layer.push({p1x, p1y});

    //dejo mis huellas almacenadas para poner el tesoro a la mitad
    vector<pair<int, int>> path;

    // Aplicar un numero random
    random_device dice;
    mt19937 gen(dice());
    
    while(!layer.empty()) {
        auto [r, c] = layer.top();
        layer.pop();

        if(r < 0 || r >= layout.size() || c < 0 || c >= layout[0].size() || (layout[r][c] != nullptr && layout[r][c]->getVisited())) {
            continue;
        }

        if(layout[r][c] == nullptr) {
            layout[r][c] = new Chunk();
        }

        layout[r][c]->setVisited(true);

        if(r == p2x && c == p2y) {
            //ubica el tesoro
            int step = path.size() % 2;
            int treasureChamber = path.size() / 2;
            if(step != 0) {
                treasureChamber -= step;
            }
            auto[tileX, tileY] = path[treasureChamber];
            layout[tileX][tileY]->setContain('$');
            checking = false;
            return;
        }

        path.push_back({r, c});

        // Explora las conexiones en las direcciones cardinales
        if(r > 0 && layout[r - 1][c] == nullptr) {
            layout[r - 1][c] = new Chunk();
        }
        if(r < rows - 1 && layout[r + 1][c] == nullptr) {
            layout[r + 1][c] = new Chunk();
        }
        if(c < cols - 1 && layout[r][c + 1] == nullptr) {
            layout[r][c + 1] = new Chunk();
        }
        if(c > 0 && layout[r][c - 1] == nullptr) {
            layout[r][c - 1] = new Chunk();
        }

        vector<int> paths = {1, 2, 3, 4};
        int passcode = 0;

        shuffle(paths.begin(), paths.end(), gen);

        for (int link : paths) {
            // Norte
            if(link == 1 && r > 0 && layout[r - 1][c] != nullptr && !layout[r - 1][c]->getVisited()) {
                layout[r][c]->setNorth(layout[r - 1][c]);
                layout[r - 1][c]->setSouth(layout[r][c]);
                passcode = 1;
                break;
            }
            // Sur
            if(link == 2 && r < rows - 1 && layout[r + 1][c] != nullptr && !layout[r + 1][c]->getVisited()) {
                layout[r][c]->setSouth(layout[r + 1][c]);
                layout[r + 1][c]->setNorth(layout[r][c]);
                passcode = 2;
                break;
            }
            // Este
            if(link == 3 && c < cols - 1 && layout[r][c + 1] != nullptr && !layout[r][c + 1]->getVisited()) {
                layout[r][c]->setEast(layout[r][c + 1]);
                layout[r][c + 1]->setWest(layout[r][c]);
                passcode = 3;
                break;
            }
            // Oeste
            if(link == 4 && c > 0 && layout[r][c - 1] != nullptr && !layout[r][c - 1]->getVisited()) {
                layout[r][c]->setWest(layout[r][c - 1]);
                layout[r][c - 1]->setEast(layout[r][c]);
                passcode = 4;
                break;
            }
        }

        if(passcode != 0) {
            if(passcode == 1) {
                layer.push({r - 1, c});
            } else if(passcode == 2) {
                layer.push({r + 1, c});
            } else if(passcode == 3) {
                layer.push({r, c + 1});
            } else if(passcode == 4) {
                layer.push({r, c - 1});
            }
        } 
        
    }
}

void Catacomb::BFS(int p1x, int p1y, int p2x, int p2y, int rows, int cols) {
    
    queue<pair<int, int>> layer;
    layer.push({p1x, p1y});

    // Dejo mis huellas almacenadas para poner el tesoro a la mitad
    vector<pair<int, int>> path;

    // Aplicar un número random
    random_device dice;
    mt19937 gen(dice());
    
    while (!layer.empty()) {
        auto [r, c] = layer.front();
        layer.pop(); 

        if (r < 0 || r >= layout.size() || c < 0 || c >= layout[0].size() || (layout[r][c] != nullptr && layout[r][c]->getVisited())) {
            continue;
        }

        if (layout[r][c] == nullptr) {
            layout[r][c] = new Chunk();
        }

        layout[r][c]->setVisited(true);

        if (r == p2x && c == p2y) {
            //Set treasure
            int step = path.size() % 2;
            int treasureChamber = path.size() / 2;
            if (step != 0) {
                treasureChamber -= step;
            }
            auto [tileX, tileY] = path[treasureChamber];
            layout[tileX][tileY]->setContain('$');
            checking = false;
            return;
        }

        path.push_back({r, c});

        // Explora las conexiones en las direcciones cardinales
        if (r > 0 && layout[r - 1][c] == nullptr) {
            layout[r - 1][c] = new Chunk();
        }
        if (r < rows - 1 && layout[r + 1][c] == nullptr) {
            layout[r + 1][c] = new Chunk();
        }
        if (c < cols - 1 && layout[r][c + 1] == nullptr) {
            layout[r][c + 1] = new Chunk();
        }
        if (c > 0 && layout[r][c - 1] == nullptr) {
            layout[r][c - 1] = new Chunk();
        }

        vector<int> paths = {1, 2, 3, 4};
        shuffle(paths.begin(), paths.end(), gen);

        for (int link : paths) {
            // Norte
            if (link == 1 && r > 0 && layout[r - 1][c] != nullptr && !layout[r - 1][c]->getVisited()) {
                layout[r][c]->setNorth(layout[r - 1][c]);
                layout[r - 1][c]->setSouth(layout[r][c]);
                layer.push({r - 1, c});
            }
            // Sur
            if (link == 2 && r < rows - 1 && layout[r + 1][c] != nullptr && !layout[r + 1][c]->getVisited()) {
                layout[r][c]->setSouth(layout[r + 1][c]);
                layout[r + 1][c]->setNorth(layout[r][c]);
                layer.push({r + 1, c}); 
            }
            // Este
            if (link == 3 && c < cols - 1 && layout[r][c + 1] != nullptr && !layout[r][c + 1]->getVisited()) {
                layout[r][c]->setEast(layout[r][c + 1]);
                layout[r][c + 1]->setWest(layout[r][c]);
                layer.push({r, c + 1}); 
            }
            // Oeste
            if (link == 4 && c > 0 && layout[r][c - 1] != nullptr && !layout[r][c - 1]->getVisited()) {
                layout[r][c]->setWest(layout[r][c - 1]);
                layout[r][c - 1]->setEast(layout[r][c]);
                layer.push({r, c - 1}); 
            }
        }
    }
}

void Catacomb::disconnect_random_nodes(){

    random_device dice;
    mt19937 gen(dice());
    uniform_int_distribution<> d2 (1, 2);

    for(int room = 0; room < layout.size(); ++room){
        for(int floor = 0; floor < layout[room].size(); ++floor){

            int link = d2(gen);
            if(layout[room][floor]->getNorth() != nullptr || layout[room][floor]->getSouth() != nullptr || layout[room][floor]->getEast() != nullptr || layout[room][floor]->getWest() != nullptr) {

                bool deadEnd = true;
                int oddLoop = 100;

                while(deadEnd && oddLoop > 0) {
                    if(link == 1 && layout[room][floor]->getWest() != nullptr) {
                        layout[room][floor]->setNorth(nullptr);
                        deadEnd = false;
                    }
                    if(link == 2 && layout[room][floor]->getEast() != nullptr) {
                        layout[room][floor]->setSouth(nullptr);
                        deadEnd = false;
                    } 
                    link = d2(gen);
                    if (link == 2) {
                        layout[room][floor]->setEast(nullptr);
                        deadEnd = false;
                    }
                    if (link == 1) {
                        layout[room][floor]->setWest(nullptr);
                        deadEnd = false;
                    }
                    link = d2(gen);
                    --oddLoop;
                }
            }
        }
    }


}

void Catacomb::connect_random_nodes(){

    random_device dice;
    mt19937 gen(dice());
    uniform_int_distribution<> d2 (1, 2);

    for(int room = 0; room < layout.size(); ++room){
        for(int floor = 0; floor < layout[room].size(); ++floor){

            int link = d2(gen);
            if(layout[room][floor]->getNorth() == nullptr && layout[room][floor]->getSouth() == nullptr && layout[room][floor]->getEast() == nullptr && layout[room][floor]->getWest() == nullptr) {

                bool deadEnd = true;
                int oddLoop = 100;

                while(deadEnd && oddLoop > 0) {
                    if(link == 1 && room > 0 && layout[room - 1][floor] != nullptr && layout[room - 1][floor]->getSouth() == nullptr) {
                        layout[room][floor]->setNorth(layout[room - 1][floor]);
                        layout[room - 1][floor]->setSouth(layout[room][floor]);
                        deadEnd = false;
                    }
                    if(link == 2 && room < layout.size() - 1 && layout[room + 1][floor] != nullptr && layout[room + 1][floor]->getNorth() == nullptr) {
                        layout[room][floor]->setSouth(layout[room + 1][floor]);
                        layout[room + 1][floor]->setNorth(layout[room][floor]);
                        deadEnd = false;
                    } 
                    link = d2(gen);
                    if (link == 2 && floor < layout[0].size() - 1 && layout[room][floor + 1] != nullptr && layout[room][floor + 1]->getWest() == nullptr) {
                        layout[room][floor]->setEast(layout[room][floor + 1]);
                        layout[room][floor + 1]->setWest(layout[room][floor]);
                        deadEnd = false;
                    }
                    if (link == 1 && floor > 0 && layout[room][floor - 1] != nullptr && layout[room][floor - 1]->getEast() == nullptr) {
                        layout[room][floor]->setWest(layout[room][floor - 1]);
                        layout[room][floor - 1]->setEast(layout[room][floor]);
                        deadEnd = false;
                    }
                    link = d2(gen);
                    --oddLoop;
                }
            }
        }
    } 

}

void Catacomb:: random_warps_and_powers(){

    int x = layout.size() - 1;
    int y = layout[0].size() - 1;

    //random numbers
    random_device dice;
    mt19937 gen(dice());
    uniform_int_distribution<> d8(1, 8);
    uniform_int_distribution<> coordenatesX(0, x);
    uniform_int_distribution<> coordenatesY(0, y);

    for(int room = 0; room < layout.size(); ++room){
        for(int floor = 0; floor < layout[room].size(); ++floor){

            int warp = d8(gen);
            int axisX = coordenatesX(gen);
            int axisY = coordenatesY(gen);
            if((warp == 1) && layout[room][floor]->getNorth() == nullptr && layout[room][floor]->getContain() != '$' && layout[axisX][axisY]) {
                layout[room][floor]->setNorth(layout[axisX][axisY]);
                layout[room][floor]->setContain('^');
            } else if((warp == 4) && layout[room][floor]->getSouth() == nullptr && layout[room][floor]->getContain() != '$' && layout[axisX][axisY]) {
                layout[room][floor]->setSouth(layout[axisX][axisY]);
                layout[room][floor]->setContain('v');
            } else if((warp == 5) && layout[room][floor]->getEast() == nullptr && layout[room][floor]->getContain() != '$' && layout[axisX][axisY]) {
                layout[room][floor]->setEast(layout[axisX][axisY]);
                layout[room][floor]->setContain('>');
            } else if((warp == 8) && layout[room][floor]->getWest() == nullptr && layout[room][floor]->getContain() != '$' && layout[axisX][axisY]) {
                layout[room][floor]->setWest(layout[axisX][axisY]);
                layout[room][floor]->setContain('<');
            }

            //asignacion de poderes
            int power = d8(gen);
            if(layout[room][floor]->getContain() == '#'){
                if(power == 1) {
                    //mindFlay
                    layout[room][floor]->setContain('@');
                } else if(power == 2){
                    //double jump
                    layout[room][floor]->setContain('&');
                }else if(power == 3){
                    //double play
                    layout[room][floor]->setContain('%');
                }
            }
        }
    }
}

void Catacomb:: tunneler(){

    //create nodes if there are nullptrs left
    for(int room = 0; room < layout.size(); ++room){
        for(int floor = 0; floor < layout[room].size(); ++floor){
            if(layout[room][floor] == nullptr) {
               layout[room][floor] = new Chunk();
            }
            if(layout[room][floor] != nullptr) {
                layout[room][floor]->setRoom(room);
                layout[room][floor]->setFloor(floor);
            } 
        }
    }

    //connect at least 1 isolated chunk (DFS)
    connect_random_nodes();

    //disconnect at least 1 chunk (BFS)
    //disconnect_random_nodes();

    //random portals and powers
    random_warps_and_powers();     
}
