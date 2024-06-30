#include "Chunk.h"

Chunk:: Chunk(int room, int floor, bool occupied, bool visited, char terrain, char contain)
            : room(room), floor(floor), occupied(occupied), visited(visited), terrain(terrain), contain(contain),
              N(nullptr), S(nullptr), E(nullptr), W(nullptr), NE(nullptr), NW(nullptr), SE(nullptr), SW(nullptr) {}

//devuelven la informacion que se les pide
int Chunk:: getRoom() const {
    return room;
}

int Chunk:: getFloor() const {
    return floor;
}

bool Chunk:: getOcuppied() const {
    return occupied;
}

bool Chunk:: getVisited() const {
    return visited;
}

char Chunk:: getTerrain() const {
    return terrain;
}

char Chunk:: getContain() const {
    return contain;
}

//cambian la informacion que se les pide
void Chunk:: setRoom(int x){
    room = x;
}

void Chunk:: setFloor(int x){
    floor = x;
}

void Chunk:: setOccupied(bool busy){
    occupied = busy;
}

//si se añade la niebla hay que modificar aquí
void Chunk:: setVisited(bool seen){
    visited = seen;
}

void Chunk:: setTerrain(char geography){
    terrain = geography;
}

void Chunk:: setContain(char holds){
    contain = holds;
}

//para añadir conexiones entre nodos
Chunk* Chunk:: getNorth() const {
    return N;
}

Chunk* Chunk:: getSouth() const {
    return S;
}

Chunk* Chunk:: getEast() const {
    return E;
}

Chunk* Chunk:: getWest() const {
    return W;
}

Chunk* Chunk:: getNorthEast() const {
    return NE;
}

Chunk* Chunk:: getNorthWest() const {
    return NW;
}

Chunk* Chunk:: getSouthEast() const {
    return SE;
}

Chunk* Chunk:: getSouthWest() const {
    return SW;
}

//aqui se le asignan las conexiones de haberlas a los nodos
void Chunk:: setNorth(Chunk* n) {
    N = n;
}

void Chunk:: setSouth(Chunk* s) {
    S = s;
}

void Chunk:: setEast(Chunk* e) {
    E = e;
}

void Chunk:: setWest(Chunk* w) {
    W = w;
}

void Chunk:: setNorthEast(Chunk* ne) {
    NE = ne;
}

void Chunk:: setNorthWest(Chunk* nw) {
    NW = nw;
}

void Chunk:: setSouthEast(Chunk* se) {
    SE = se;
}

void Chunk:: setSouthWest(Chunk* sw) {
    SW = sw;
}