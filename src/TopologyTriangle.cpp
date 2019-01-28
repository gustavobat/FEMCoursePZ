/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TopologyTriangle.h"
#include "tpanic.h"

int TopologyTriangle::NSideNodes(int side) {
    if (side > 6) {
        DebugStop();
    }

    int nsidenodes[7] = {1, 1, 1, 2, 2, 2, 4};
    return nsidenodes[side];
}

int TopologyTriangle::SideNodeIndex(int side, int node) {
    if(side < 3 && node == 0) {
        return side;
    }

    else if(side >= 3 && side < 6 && node < 2) {
        return (side + node) % 3;
    }

    else if(side == 6 && node < 3) {
        return node;
    }

    else {
        DebugStop();
        return -1;
    }
}

ElementType TopologyTriangle::Type() {
    ETriangle;
}
