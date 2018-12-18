/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "IntRule.h"
#include "tpanic.h"
#include <iomanip>

IntRule::IntRule() : fPoints(1, 1), fWeights(0), fOrder(-1) {
}

IntRule::IntRule(int order) {
    DebugStop();
}

IntRule::~IntRule() {

}

IntRule::IntRule(const IntRule& copy) {
    DebugStop();
}

IntRule &IntRule::operator=(const IntRule &cp) {
    DebugStop();
}

int IntRule::NPoints() const {
    DebugStop();
}

void IntRule::Print(std::ostream &out) {

    out << ":: Integration Rule Info" << std::endl;
    out << " Order: " << fOrder << std::endl;

    for (auto i = 0; i < fPoints.Rows();  i++) {

        out << std::fixed << std::setprecision(printPrecision)
            << " Point: " << std::left << std::setw(5) << i
            << " x: " << std::left << std::setw(15) << fPoints(i, 0)
            << " w: " << std::left << std::setw(15) << fWeights[i]
            <<  std::endl;
    }
}

void IntRule::Point(int p, VecDouble& co, double& w) const {
    DebugStop();
}
