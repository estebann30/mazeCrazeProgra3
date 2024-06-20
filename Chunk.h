#ifndef CHUNK_H
#define CHUNK_H

using namespace std;

class Chunk {
    
    private:
    
        //posicion en X
        int room;

        //posicion en Y
        int floor;

        //hay un jugador dentro?
        bool occupied = false;

        //fue visitado?
        bool visited = false;

        //está inexplorado? Es baldosa o pared?
        char terrain = 'u';

        //que contiene? Ej: vacío, tesoro, portal, poder, etc...
        char contain = 'v';

        //Conecciones entre chunks MODULARES?
        Chunk* N;
        Chunk* S;
        Chunk* E;
        Chunk* W;

        //util para los modulares de triangulo y hexagono
        Chunk* NE;
        Chunk* NW;
        Chunk* SE;
        Chunk* SW;

    public:

        Chunk(int room = 0, int floor = 0, bool occupied = false, bool visited = false, char terrain = 'u', char contain = 'v');

        //devuelven la informacion que se les pide
        int getRoom() const;
        int getFloor() const;
        bool getOcuppied() const;
        bool getVisited() const;
        char getTerrain() const;
        char getContain() const;

        //cambian la informacion que se les pide
        void setRoom(int x);
        void setFloor(int x);
        void setOccupied(bool busy);

        //si se añade la niebla hay que modificar aquí
        void setVisited(bool seen);
        
        void setTerrain(char geography);
        void setContain(char holds);

        //para añadir conexiones entre nodos
        Chunk* getNorth() const;
        Chunk* getSouth() const;
        Chunk* getEast() const;
        Chunk* getWest() const;
        Chunk* getNorthEast() const;
        Chunk* getNorthWest() const;
        Chunk* getSouthEast() const;
        Chunk* getSouthWest() const;

        //aqui se le asignan las conexiones de haberlas a los nodos
        void setNorth(Chunk* n);
        void setSouth(Chunk* s);
        void setEast(Chunk* e);
        void setWest(Chunk* w);
        void setNorthEast(Chunk* ne);
        void setNorthWest(Chunk* nw);
        void setSouthEast(Chunk* se);
        void setSouthWest(Chunk* sw);
};


// int main(){
//     Chunk block(0 , 0, false, false, 'u', 'v');

//     block.setRoom(2);

//     int dato = block.getRoom();


//     cout << "El dato que buscas es: " << dato << "\n";

//     return 0;
// }

#endif