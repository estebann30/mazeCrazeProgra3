#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Explorer.h"

class Controller {
    private:
    int flayed;
    public:
    Controller();

    void pad(Explorer& explorer);
};

#endif