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
    switch (side) {
        case 0:
        case 1:
        case 2:
        case 3:
            return 1;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            return order - 1;
        case 10:
        case 11:
        case 12:
        case 13: {
            int sum = 0;
            for (int i = 0; i < order - 1; i++) sum += i;
            return sum;
        }
        case 14: {
            int sum = 0;
            for (int i = 1; i < order - 2; i++) {
                sum += i * (i + 1) / 2;
            }
            return sum;
        }
        default: {
            DebugStop();
            std::cout << "ShapeTetrahedron::NShapeFunctions, bad parameter side " << std::endl;
            return 0;
        }
    }
}

int ShapeTetrahedron::NShapeFunctions(VecInt &orders) {
    auto n = orders.size();

    int nShapeFunctions = 0;
    for (auto i = 0; i < n; i++) {
        nShapeFunctions += NShapeFunctions(i, orders[i]);
    }

    return nShapeFunctions;
}
