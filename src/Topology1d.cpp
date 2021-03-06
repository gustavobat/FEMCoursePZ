/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Topology1d.h"
#include "tpanic.h"

int Topology1d::NSideNodes(int side) {
    if (side > 2) {
        DebugStop();
    }

    int nsidenodes[3] = {1, 1, 2};
    return nsidenodes[side];
}

int Topology1d::SideNodeIndex(int side, int node) {
    if(side < 2 && node == 0) {
        return side;
    }

    else if(side == 2 && node < 2) {
        return node;
    }

    else {
        DebugStop();
        return -1;
    }
}

ElementType Topology1d::Type() {
    return ELine;
}
