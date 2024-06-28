#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <algorithm>
#include <queue>
#include "Catacomb.h"

using namespace std;

Catacomb:: Catacomb() {}

void Catacomb:: mazeMapping() {
    int rooms = 5;
    int floors = 5;
    
    layout = vector<vector<Chunk*>>(rooms, vector<Chunk*>(floors, nullptr));
    //cout << endl << "Im working" << endl;

    // try {
    //     DFS(0, 0, rooms -1, floors -1, rooms, floors);
    // } catch(const exception& e) {
    //     cerr << "Exception caught in mazeMapping: " << e.what() << ". Retrying DFS..." << endl;
    //     //mi respaldo
    //     layout = vector<vector<Chunk*>>(rooms, vector<Chunk*>(floors, nullptr));
    //     DFS(0, 0, rooms -1, floors -1, rooms, floors);
    // }

    try {
        BFS(0, 0, rooms -1, floors -1, rooms, floors);
    } catch(const exception& e) {
        cerr << "Exception caught in mazeMapping: " << e.what() << ". Retrying BFS..." << endl;
        //mi respaldo
        layout = vector<vector<Chunk*>>(rooms, vector<Chunk*>(floors, nullptr));
        BFS(0, 0, rooms -1, floors -1, rooms, floors);
    }
}

vector<vector<Chunk*>>& Catacomb:: mapped() {
    return layout;
}


//METER TESORO!!!!!!!!!

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
        path.push_back({r, c});

        if(r == p2x && c == p2y) {
            //cout << "destino r = " << r << endl;
            //cout << "destino c = " << c << endl;

            //ubica el tesoro
            int step = path.size() % 2;
            int treasureChamber = path.size() / 2;
            if(step != 0) {
                treasureChamber -= step;
            }
            auto[tileX, tileY] = path[treasureChamber];
            layout[tileX][tileY]->setContain('$');
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

//CAMBIAR

void Catacomb::BFS(int p1x, int p1y, int p2x, int p2y, int rows, int cols) {


    // Aplicar un numero random
    random_device dice;
    mt19937 gen(dice());

    //Create a queue for BFS
    queue<pair<int, int>> layer;

    //Starting node added to queue
    layer.push({p1x, p1y});

    //Continue until queue is empty

    while(!layer.empty()){
        //Get the front of the queue and remove it
        auto [r, c] = layer.front();
        layer.pop();

        if (r < 0 || r >= layout.size() || c < 0 || c >= layout[0].size() || (layout[r][c] != nullptr && layout[r][c]->getVisited())) {
            continue;
        }

        cout << "Procesando celda: (" << r << ", " << c << ")" << endl;

        if (layout[r][c] == nullptr) {
             layout[r][c] = new Chunk();
        }

        layout[r][c]->setVisited(true);


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

        //aqui se hace la logica de la busqueda como tal
        vector<int> paths = {0, 1, 2, 3};
        random_shuffle(paths.begin(), paths.end(), gen);

        //revisar esto

        
        // for (int i = 0; i < 4; i++) {
        //     int nx = x + dx[directions[i]];
        //     int ny = y + dy[directions[i]];

        //     if (isValid(nx, ny, rows, cols, visited)) {
        //         visited[nx][ny] = true;
        //         q.push({nx, ny});
                
        //         // Aquí puedes agregar lógica adicional para conectar los nodos y generar caminos
        //         // Por ejemplo, puedes marcar las celdas en una matriz que represente el laberinto
        //         cout << "Conectando (" << x << ", " << y << ") con (" << nx << ", " << ny << ")" << endl;
        //     }
        // }

    }


    //
//     queue<pair<int, int>> layer;
//     layer.push({p1x, p1y});

// // Aplicar un numero random
// random_device dice;
// mt19937 gen(dice());

// while (!layer.empty()) {
//     auto [r, c] = layer.front();
//     layer.pop();

//     cout << "Procesando celda: (" << r << ", " << c << ")" << endl;

//     if (r < 0 || r >= layout.size() || c < 0 || c >= layout[0].size() || (layout[r][c] != nullptr && layout[r][c]->getVisited())) {
//         continue;
//     }

//     if (layout[r][c] == nullptr) {
//         layout[r][c] = new Chunk();
//     }

//     layout[r][c]->setVisited(true);

//     if (r == p2x && c == p2y) {
//         cout << "Destino alcanzado en: (" << r << ", " << c << ")" << endl;
//         break;
//     }

//     // Explora las conexiones en las direcciones cardinales
//     if (r > 0 && layout[r - 1][c] == nullptr) {
//         layout[r - 1][c] = new Chunk();
//     }
//     if (r < rows - 1 && layout[r + 1][c] == nullptr) {
//         layout[r + 1][c] = new Chunk();
//     }
//     if (c < cols - 1 && layout[r][c + 1] == nullptr) {
//         layout[r][c + 1] = new Chunk();
//     }
//     if (c > 0 && layout[r][c - 1] == nullptr) {
//         layout[r][c - 1] = new Chunk();
//     }

//     vector<int> paths = {1, 2, 3, 4};
//     int passcode = 0;
//     int oddLoop = 1000;
//     shuffle(paths.begin(), paths.end(), gen);

//     while(passcode == 0 && oddLoop > 0){
//         for (int link : paths) {
//             // Norte
//             if(link == 1 && r > 0 && layout[r - 1][c] != nullptr && !layout[r - 1][c]->getVisited()) {
//                 layout[r][c]->setNorth(layout[r - 1][c]);
//                 layout[r - 1][c]->setSouth(layout[r][c]);
//                 passcode = 1;
//                 break;
//             }
//             // Sur
//             if(link == 2 && r < rows - 1 && layout[r + 1][c] != nullptr && !layout[r + 1][c]->getVisited()) {
//                 layout[r][c]->setSouth(layout[r + 1][c]);
//                 layout[r + 1][c]->setNorth(layout[r][c]);
//                 passcode = 2;
//                 break;
//             }
//             // Este
//             if(link == 3 && c < cols - 1 && layout[r][c + 1] != nullptr && !layout[r][c + 1]->getVisited()) {
//                 layout[r][c]->setEast(layout[r][c + 1]);
//                 layout[r][c + 1]->setWest(layout[r][c]);
//                 passcode = 3;
//                 break;
//             }
//             // Oeste
//             if(link == 4 && c > 0 && layout[r][c - 1] != nullptr && !layout[r][c - 1]->getVisited()) {
//                 layout[r][c]->setWest(layout[r][c - 1]);
//                 layout[r][c - 1]->setEast(layout[r][c]);
//                 passcode = 4;
//                 break;
//             }
//         }

//         if(passcode != 0) {
//             if(passcode == 1) {
//                 layer.push({r - 1, c});
//                 cout << "Moviendo al norte a: (" << r - 1 << ", " << c << ")" << endl;
//             } else if(passcode == 2) {
//                 layer.push({r + 1, c});
//                 cout << "Moviendo al sur a: (" << r + 1 << ", " << c << ")" << endl;
//             } else if(passcode == 3) {
//                 layer.push({r, c + 1});
//                 cout << "Moviendo al este a: (" << r << ", " << c + 1 << ")" << endl;
//             } else if(passcode == 4) {
//                 layer.push({r, c - 1});
//                 cout << "Moviendo al oeste a: (" << r << ", " << c - 1 << ")" << endl;
//             }
//         } else {
//             if(r + 1 < rows) {
//                 r = r + 1;
//                 cout << "Forzando movimiento al sur a: (" << r << ", " << c << ")" << endl;
//             } else if(c + 1 < cols) {
//                 c = c + 1;
//                 cout << "Forzando movimiento al este a: (" << r << ", " << c << ")" << endl;
//             } else {
//                 cout << "Exploté en: (" << r << ", " << c << ")" << endl;
//                 break;
//             }
//             --oddLoop;
//         }

//         if (oddLoop <= 0) {
//             throw runtime_error("Bucle infinito detectado en BFS");
//         }
//     }
// }

// throw runtime_error("Condición de error encontrada en BFS");


}

// hacer un void que agregue nodos restantes y conecte random con poderes
void Catacomb:: tunneler(){

    int x = layout.size() - 1;
    int y = layout[0].size() - 1;

    // Aplicar un numero random
    random_device dice;
    mt19937 gen(dice());
    uniform_int_distribution<> d2 (1, 2);
    uniform_int_distribution<> d8(1, 8);
    uniform_int_distribution<> coordenatesX(0, x);
    uniform_int_distribution<> coordenatesY(0, y);
    
    //crea nodos donde no hay aun
    for(int room = 0; room < layout.size(); ++room){
        for(int floor = 0; floor < layout[room].size(); ++floor){
            if(layout[room][floor] == nullptr) {
               layout[room][floor] = new Chunk();
            }
            if(layout[room][floor] != nullptr) {
                layout[room][floor]->setRoom(room);
                layout[room][floor]->setFloor(floor);
            } 
            
            int link = d2(gen);

            //conecta al menos 1 vez chunk aislados
            if(layout[room][floor]->getNorth() == nullptr && layout[room][floor]->getSouth() == nullptr && layout[room][floor]->getEast() == nullptr && layout[room][floor]->getWest() == nullptr) {

                bool deadEnd = true;
                while(deadEnd) {
                    if(link == 1 && room > 0 && layout[room - 1][floor] != nullptr && layout[room - 1][floor]->getSouth() == nullptr) {
                        layout[room][floor]->setNorth(layout[room - 1][floor]);
                        layout[room - 1][floor]->setSouth(layout[room][floor]);
                        deadEnd = false;
                    }
                    //link = d2(gen);
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
                    //link = d2(gen);
                    if (link == 1 && floor > 0 && layout[room][floor - 1] != nullptr && layout[room][floor - 1]->getEast() == nullptr) {
                        layout[room][floor]->setWest(layout[room][floor - 1]);
                        layout[room][floor - 1]->setEast(layout[room][floor]);
                        deadEnd = false;
                    }
                    link = d2(gen);
                }
            }

            int warp = d8(gen);
            int axisX = coordenatesX(gen);
            int axisY = coordenatesY(gen);

            //portales random
            if((warp == 1 || warp == 2) && layout[room][floor]->getNorth() == nullptr && layout[room][floor]->getContain() != '$') {
                layout[room][floor]->setNorth(layout[axisX][axisY]);
                layout[room][floor]->setContain('w');
            } else if((warp == 1 || warp == 2) && layout[room][floor]->getSouth() == nullptr && layout[room][floor]->getContain() != '$') {
                layout[room][floor]->setSouth(layout[axisX][axisY]);
                layout[room][floor]->setContain('w');
            } else if((warp == 1 || warp == 2) && layout[room][floor]->getEast() == nullptr && layout[room][floor]->getContain() != '$') {
                layout[room][floor]->setEast(layout[axisX][axisY]);
                layout[room][floor]->setContain('w');
            } else if((warp == 1 || warp == 2) && layout[room][floor]->getWest() == nullptr && layout[room][floor]->getContain() != '$') {
                layout[room][floor]->setWest(layout[axisX][axisY]);
                layout[room][floor]->setContain('w');
            }

            int power = d8(gen);
            //asignacion de poderes
            if(layout[room][floor]->getContain() == '#'){
                if(power == 1) {
                    //mindFlay
                    layout[room][floor]->setContain('@');
                } else if(power == 2){
                    //double jump
                    layout[room][floor]->setContain('&');
                }
            }
        }
    }
}

//faltan
//saltos sobre paredes
//verificar mindflay
//desaparecer poder al usarlo
//verificar que se añaden poderes
