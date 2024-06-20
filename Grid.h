#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Node.h"

// Clase que maneja la matriz de nodos
class Grid {
public:
    // Constructor que inicializa la matriz con el tamaño dado
    Grid(int width, int height);

    // Método para obtener un nodo en una posición específica
    Node& getNode(int x, int y);

    // Método para establecer un nodo en una posición específica
    void setNode(int x, int y, const Node& node);

    // Métodos para obtener el ancho y la altura de la matriz
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int width; // Ancho de la matriz
    int height; // Altura de la matriz
    std::vector<std::vector<Node>> nodes; // Matriz de nodos
};

#endif // GRID_H
