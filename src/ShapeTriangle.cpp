/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ShapeTriangle.h"
#include "tpanic.h"

void ShapeTriangle::Shape(const VecDouble &xi, VecInt &orders, VecDouble &phi, Matrix &dphi) {
    DebugStop();
}

int ShapeTriangle::NShapeFunctions(int side, int order) {
    switch(side) {
        case 0:
        case 1:
        case 2:
            return 1;
        case 3:
        case 4:
        case 5:
        case 6:
            return order-1;
    }

    DebugStop();
    std::cout << "ShapeTriangle::NShapeFunctions, bad parameter side " << std::endl;
    return 0;
}

int ShapeTriangle::NShapeFunctions(VecInt &orders) {
    auto n = orders.size();

    int nShapeFunctions = 0;
    for (auto i = 0; i < n; i++) {
        nShapeFunctions += NShapeFunctions(i, orders[i]);
    }

    return nShapeFunctions;
}
