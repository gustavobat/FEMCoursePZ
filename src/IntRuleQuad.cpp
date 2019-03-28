/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "IntRuleQuad.h"
#include "IntRule1d.h"
#include "tpanic.h"

IntRuleQuad::IntRuleQuad() {
    fOrder = -1;
    fPoints.Resize(1, 1);
    fWeights.resize(0);
}

IntRuleQuad::IntRuleQuad(int order) {
    SetOrder(order);
}

void IntRuleQuad::SetOrder(int order) {
    if (order < 0) {
        DebugStop();
    }

    int nPoints;
    int resto = fOrder % 2;

    if (resto != 0) {
        nPoints = (fOrder + 1) / 2;
    }

    if (resto == 0) {
        nPoints = (fOrder + 2) / 2;
    }

    fPoints.Resize(nPoints * nPoints, 2);
    fWeights.resize(nPoints * nPoints);

    VecDouble co(nPoints);
    VecDouble w(nPoints);

    this->gaulegQuad(-1, 1, co, w);

    for (int i = 0; i < nPoints; i++) {
        for (int j = 0; j < nPoints; j++) {
            fPoints(j + i * nPoints, 0) = co[j + i * nPoints];
            fPoints(j + i * nPoints, 1) = co[j + i * nPoints + nPoints * nPoints];

            fWeights[j + i * nPoints] = w[i];
        }
    }
}

void IntRuleQuad::gaulegQuad(const double x1, const double x2, VecDouble &co, VecDouble &w) {
    IntRule1d x;
    IntRule1d y;

    int nPoints = co.size();

    VecDouble cox(nPoints);
    VecDouble coy(nPoints);
    VecDouble wx(nPoints);
    VecDouble wy(nPoints);

    x.gauleg(x1, x2, cox, wx);
    y.gauleg(x1, x2, coy, wy);

    co.resize(2 * nPoints * nPoints);
    w.resize(nPoints * nPoints);

    for (int i = 0; i < nPoints; i++) {
        for (int j = 0; j < nPoints; j++) {
            co[j + i * nPoints] = cox[j];
            co[j + i * nPoints + nPoints * nPoints] = coy[i];
            w[nPoints * i + j] = wx[i] * wy[j];
        }
    }
}
