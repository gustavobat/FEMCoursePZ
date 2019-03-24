/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Shape1d.h"
#include "tpanic.h"

void Shape1d::Shape(const VecDouble& xi, VecInt& orders, VecDouble& phi, Matrix& dphi) {
    if (orders[0] < 0 || orders[1] < 0 || orders[0] > 1) {
        DebugStop();
    }

    int nShapeFunctions = NShapeFunctions(orders);

    phi.resize(nShapeFunctions);
    dphi.Resize(1, nShapeFunctions);

    if (orders[0] == 0) {
        phi[0] = 1.;
        dphi(0,0) = 0.;
    }
    else {
        phi[0] = (1 - xi[0]) / 2.;
        phi[1] = (1 + xi[0]) / 2.;
        dphi(0,0) = -0.5;
        dphi(0,1) = 0.5;
    }
    if (orders[0] == 2) {
        phi[2] = 4. * phi[0] * phi[1];
        dphi(0,2) = 4. * (dphi(0,0) * phi[1]) + (dphi(0,1) * phi[0]);
    }
}

int Shape1d::NShapeFunctions(int side, int order) {
    if (side < 2) {
        return 1;
    }

    if (side == 2) {
        return (order - 1);
    }

    DebugStop();
    return -1;
}

int Shape1d::NShapeFunctions(VecInt &orders) {
    auto n = orders.size();

    int nShapeFunctions = 0;
    for (auto i = 0; i < n; i++) {
        nShapeFunctions += NShapeFunctions(i, orders[i]);
    }

    return nShapeFunctions;
}
