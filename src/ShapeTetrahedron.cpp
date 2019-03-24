/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ShapeTetrahedron.h"
#include "tpanic.h"

void ShapeTetrahedron::Shape(const VecDouble &xi, VecInt &orders, VecDouble &phi, Matrix &dphi) {
    DebugStop();
}

int ShapeTetrahedron::NShapeFunctions(int side, int order) {
    DebugStop();
}

int ShapeTetrahedron::NShapeFunctions(VecInt &orders) {
    auto n = orders.size();

    int nShapeFunctions = 0;
    for (auto i = 0; i < n; i++) {
        nShapeFunctions += NShapeFunctions(i, orders[i]);
    }

    return nShapeFunctions;
}
