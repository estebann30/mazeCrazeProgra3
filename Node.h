#ifndef NODE_H
#define NODE_H

class Node {
public:
    bool hasPower1;
    bool hasPower2;
    bool hasPower3;
    bool hasPower4;
    bool wallUp;
    bool wallDown;
    bool wallLeft;
    bool wallRight;
    bool hasPlayer1;  // Campo adicional para el jugador 1
    bool hasPlayer2;  // Campo adicional para el jugador 2

    Node()
        : hasPower1(false), hasPower2(false), hasPower3(false), hasPower4(false),
          wallUp(false), wallDown(false), wallLeft(false), wallRight(false),
          hasPlayer1(false), hasPlayer2(false) {}
};

#endif // NODE_H

