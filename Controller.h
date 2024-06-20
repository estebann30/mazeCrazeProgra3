#ifndef CONTROLLER_H
#define CONTROLLER_H

//#include "Dungeon.h"
#include "Catacomb.h"

class Controller {
    public:
        Controller();

        void pad(Catacomb& maze);
};

#endif