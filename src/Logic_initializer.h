#ifndef LOGIC_INITIALIZER_H
#define LOGIC_INITIALIZER_H

#include "Controller.h"
#include "Explorer.h"

using namespace std;

class Logic_initializer{
    public:
    Explorer explorer;
    private:
        Logic_initializer();
        void initialize();

};

#endif