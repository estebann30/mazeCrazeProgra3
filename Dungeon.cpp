#include <iostream>
#include <vector>
#include "Chunk.h"
#include "Dungeon.h"

using namespace std;

Dungeon:: Dungeon() {}

void Dungeon:: mazeMapping(int rows, int cols){
    layout = vector<vector<Chunk>>(rows, vector<Chunk>(cols, 0));

    for(int room = 0; room < rows; ++room){
        for(int floor = 0; floor < cols; ++floor){
            layout[room][floor].setRoom(room);
            layout[room][floor].setFloor(floor);
        }
    }
}

void Dungeon:: tester() {
    cout << "Im working!" << endl;

    for (int room = 0; room < layout.size(); ++room) {
        for (int floor = 0; floor < layout[room].size(); ++floor) {
            cout << "[" << layout[room][floor].getRoom() << ", " << layout[room][floor].getFloor() << "]";
        }
        cout << endl;
    }
}




// int main(){
//     Dungeon maze;

//     maze.mazeMapping(5 ,5);

//     maze.tester();


//     //cout << "Presionaste la tecla: " << "\n";

//     return 0;
// }