#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <algorithm>
#include "Catacomb.h"

using namespace std;

Catacomb:: Catacomb() : explorer() {}

Explorer& Catacomb:: explorers() {
    return explorer;
}

void Catacomb:: mazeMapping(int rows, int cols) {
    layout = vector<vector<Chunk*>>(rows, vector<Chunk*>(cols, nullptr));
    //cout << endl << "Im working" << endl;

    try {
        DFS(0, 0, rows -1, cols -1, rows, cols);
    } catch(const exception& e) {
        cerr << "Exception caught in mazeMapping: " << e.what() << ". Retrying DFS..." << endl;
        //mi respaldo
        layout = vector<vector<Chunk*>>(rows, vector<Chunk*>(cols, nullptr));
        DFS(0, 0, rows -1, cols -1, rows, cols);
    }
}



void Catacomb::DFS(int p1x, int p1y, int p2x, int p2y, int rows, int cols) {
    stack<pair<int, int>> layer;
    layer.push({p1x, p1y});

    // Aplicar un numero random
    random_device dice;
    mt19937 gen(dice());
    uniform_int_distribution<> faces(1, 4);

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
            cout << "destino r = " << r << endl;
            cout << "destino c = " << c << endl;
            return;
        }

        // Explora las conexiones en las direcciones cardinales
        if(r > 0 && layout[r - 1][c] == nullptr) {
            layout[r - 1][c] = new Chunk();
        }
        if(r < rows - 1 && layout[r + 1][c] == nullptr) {
            layout[r + 1][c] = new Chunk();

            // if(layout[r + 1][c] == layout[p2x][p2y]){
            //     layout[r][c]->setSouth(layout[r + 1][c]);
            //     layout[r + 1][c]->setNorth(layout[r][c]);
            //     cout << "sali con r = " << r << endl;
            //     cout << "sali con c = " << c << endl;
            //     return;
            // }
        }
        if(c < cols - 1 && layout[r][c + 1] == nullptr) {
            layout[r][c + 1] = new Chunk();

            // if(layout[r][c + 1] == layout[p2x][p2y]){
            //     layout[r][c]->setEast(layout[r][c + 1]);
            //     layout[r][c + 1]->setWest(layout[r][c]);
            //     cout << "sali con r = " << r << endl;
            //     cout << "sali con c = " << c << endl;
            //     return;
            // }
        }
        if(c > 0 && layout[r][c - 1] == nullptr) {
            layout[r][c - 1] = new Chunk();
        }

        vector<int> paths = {1, 2, 3, 4};
        int passcode = 0;
        int oddLoop = 1000;

        shuffle(paths.begin(), paths.end(), gen);

        while(passcode == 0 && oddLoop > 0){

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
            } else {
                if(r + 1 < rows - 1) {
                    r = r + 1;
                }
                if(c + 1 < cols - 1) {
                    c = c + 1;
                }
                //cout << endl << "exploté en: " << r << ", " << c << endl;
                --oddLoop;
            }
        }
    }
    throw runtime_error("Condición de error encontrada en DFS");
}


void Catacomb:: thombRaider() {

    for(int room = 0; room < layout.size(); ++room){
        for(int floor = 0; floor < layout[room].size(); ++floor){
            if(layout[room][floor] != nullptr) {
                layout[room][floor]->setRoom(room);
                layout[room][floor]->setFloor(floor);
            } 
        }
    }

    // //metodo para visualizar los indicadores numericos de los nodos
    // for(int room = 0; room < layout.size(); ++room){
    //     for(int floor = 0; floor < layout[room].size(); ++floor){
    //         if(layout[room][floor] != nullptr) {
    //             cout << "[" << layout[room][floor]->getRoom() << ", " << layout[room][floor]->getFloor() << "]";
    //         } else {
    //             cout << "      ";
    //         }
    //         cout << " ";
    //     }
    //     cout << endl;
    // }

    int row = layout.size() * 2 + 1;
    int col = layout[0].size() * 2 + 1;
    vector<vector<char>> thomb(row, vector<char>(col, ' '));

    for(int r = 0; r < layout.size(); ++r){
        for(int c = 0; c < layout[0].size(); ++c){
            
            int rr = r * 2 + 1;
            int cc = c * 2 + 1;

            if(layout[r][c] == nullptr){
                thomb[rr][cc] = ' ';
            } else {
                thomb[rr][cc] = ' ';

                if(layout[r][c]->getFloor() == explorer.getX(1) && layout[r][c]->getRoom() == explorer.getY(1)) {
                    thomb[rr][cc] = '1';
                } else if(layout[r][c]->getFloor() == explorer.getX(2) && layout[r][c]->getRoom() == explorer.getY(2)) {
                    thomb[rr][cc] = '2';
                }

                if(layout[r][c] != nullptr) {
                    if(layout[r][c]->getEast() != nullptr) {
                        thomb[rr][cc + 1] = '-';
                    }
                    if(layout[r][c]->getSouth() != nullptr) {
                        thomb[rr + 1][cc] = '|';
                    }
                    if(layout[r][c]->getWest() != nullptr) {
                        thomb[rr][cc - 1] = '-';
                    }
                    if(layout[r][c]->getNorth() != nullptr) {
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