#include "Grid.h"

// Constructor que inicializa la matriz con nodos vacíos
Grid::Grid(int width, int height)
    : width(width), height(height), nodes(width, std::vector<Node>(height)) {}

// Método para obtener un nodo en una posición específica
Node& Grid::getNode(int x, int y) {
    return nodes[x][y];
}

// Método para establecer un nodo en una posición específica
void Grid::setNode(int x, int y, const Node& node) {
    nodes[x][y] = node;
}
