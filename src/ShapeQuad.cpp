/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ShapeQuad.h"
#include "tpanic.h"

void ShapeQuad::Shape(const VecDouble &xi, VecInt &orders, VecDouble &phi, Matrix &dphi) {

    if (orders[0] < 0) {
        std::cout << "Invalid negative order." << std::endl;
        DebugStop();
    }

    if (orders[0] > 2) {
        std::cout << "Shape functions only implemented until order 2." << std::endl;
        DebugStop();
    }

    REAL x[2], dx[2], y[2], dy[2];
    x[0] = (1. - xi[0]) / 2.;
    x[1] = (1. + xi[0]) / 2.;
    dx[0] = -0.5;
    dx[1] = 0.5;
    y[0] = (1. - xi[1]) / 2.;
    y[1] = (1. + xi[1]) / 2.;
    dy[0] = -0.5;
    dy[1] = 0.5;
    phi[0] = x[0] * y[0];
    phi[1] = x[1] * y[0];
    phi[2] = x[1] * y[1];
    phi[3] = x[0] * y[1];
    dphi(0, 0) = dx[0] * y[0];
    dphi(1, 0) = x[0] * dy[0];
    dphi(0, 1) = dx[1] * y[0];
    dphi(1, 1) = x[1] * dy[0];
    dphi(0, 2) = dx[1] * y[1];
    dphi(1, 2) = x[1] * dy[1];
    dphi(0, 3) = dx[0] * y[1];
    dphi(1, 3) = x[0] * dy[1];

    if (orders[0] == 2) {
        int is;
        for (is = 4; is < 8; is++) {
            phi[is] = phi[is % 4] * phi[(is + 1) % 4];
            dphi(0, is) = dphi(0, is % 4) * phi[(is + 1) % 4] + phi[is % 4] * dphi(0, (is + 1) % 4);
            dphi(1, is) = dphi(1, is % 4) * phi[(is + 1) % 4] + phi[is % 4] * dphi(1, (is + 1) % 4);
        }

        phi[8] = phi[0] * phi[2];
        dphi(0, 8) = dphi(0, 0) * phi[2] + phi[0] * dphi(0, 2);
        dphi(1, 8) = dphi(1, 0) * phi[2] + phi[0] * dphi(1, 2);

        // Make the generating shape functions linear and unitary
        for (is = 4; is < 8; is++) {
            phi[is] += phi[8];
            dphi(0, is) += dphi(0, 8);
            dphi(1, is) += dphi(1, 8);
            phi[is] *= 4.;
            dphi(0, is) *= 4.;
            dphi(1, is) *= 4.;
        }

        phi[8] *= 16.;
        dphi(0, 8) *= 16.;
        dphi(1, 8) *= 16.;
    }
}

int ShapeQuad::NShapeFunctions(int side, int order) {
    if (side >= 0 && side < 4) {
        return 1; // Points
    } else if (side < 8) {
        return (order - 1); // Edges
    } else if (side == 8) {
        return ((order - 1) * (order - 1)); // Surface
    }

    std::cout << "Side value not valid." << std::endl;
    DebugStop();
    return 0;
}

int ShapeQuad::NShapeFunctions(VecInt &orders) {
    auto n = orders.size();

    int nShapeFunctions = 0;
    for (auto i = 0; i < n; i++) {
        nShapeFunctions += NShapeFunctions(i, orders[i]);
    }

    return nShapeFunctions;
}
