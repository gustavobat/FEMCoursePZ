#include <iostream>
#include <fstream>
#include <math.h>
#include <TMatrix.h>

#include <GeoNode.h>

#include "IntRule1d.h"

int main () {

    VecDouble coordinates(3);
    coordinates[0] = 1.2;
    coordinates[1] = 1.433;
    coordinates[2] = -.7;

    GeoNode node(coordinates);
    node.Print(std::cout);

    return 0;
}

