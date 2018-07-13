/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "IntRule.h"
#include "tpanic.h"

using namespace std;

IntRule::IntRule() : fPoints(), fWeights(0){
    DebugStop();
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
    DebugStop();
}

void IntRule::Point(int p, VecDouble& co, double& w) const {
    DebugStop();
}
