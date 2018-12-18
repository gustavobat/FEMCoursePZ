/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "IntRule1d.h"
#include "tpanic.h"

#define PI 3.1415926535898

IntRule1d::IntRule1d() {
    fOrder = -1;
    fPoints.Resize(1, 1);
    fWeights.resize(0);
}

IntRule1d::IntRule1d(int order) {
    fPoints.Resize(1, 1);
    fWeights.resize(0);

    if (order < 0) {
        DebugStop();
    }
    SetOrder(order);
}

void IntRule1d::SetOrder(int order) {

    if (order < 0) {
        DebugStop();
    }

    fOrder = order;
    int nPoints = order + 1;
    fPoints.Resize(nPoints, 1);
    fWeights.resize(nPoints);

    gauleg(-1, 1, fPoints, fWeights);
}

/*
 * Reference: Press et al. Numerical Recipes: The Art of Scientific Computing. (3 ed.). Page: 184
 */
void IntRule1d::gauleg(const double x1, const double x2, Matrix &co, VecDouble &w) {

    double z, z1, pp, p1, p2, p3;

    auto nPoints = co.Rows();
    double m = (nPoints + 1) / 2.;
    double xm = (x1 + x2) / 2.;
    double xl = (x2 - x1) / 2.;

    for (auto i = 0; i < m; i++) {

        // Initial root approximation
        z = cos(PI * (i + 0.75) / (nPoints + 0.5));

        do {
            p1 = 1.0;
            p2 = 0.0;

            for (auto j = 0; j < nPoints; j++) {
                p3 = p2;
                p2 = p1;
                p1 = ((2.0 * j + 1.0) * z * p2 - j * p3) / (j + 1);
            }

            pp = nPoints * (z * p1 - p2) / (z * z - 1.0);
            z1 = z;
            z = z1 - p1 / pp;
        } while (std::abs(z - z1) > EPS);

        co(i, 0) = xm - xl * z;
        co(nPoints - 1 - i, 0) = xm + xl * z;
        w[i] = 2.0 * xl / ((1.0 - z * z) * pp * pp);
        w[nPoints - 1 - i] = w[i];
    }
}
