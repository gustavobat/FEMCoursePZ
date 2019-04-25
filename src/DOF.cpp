/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "DOF.h"
#include "tpanic.h"

DOF::DOF() : firstequation(0), nshape(0), nstate(0), order(0) {

}

DOF::DOF(const DOF &copy) {
    firstequation = copy.firstequation;
    nshape = copy.nshape;
    nstate = copy.nstate;
    order = copy.order;
}

DOF &DOF::operator=(const DOF &copy) {
    firstequation = copy.firstequation;
    nshape = copy.nshape;
    nstate = copy.nstate;
    order = copy.order;
    return *this;
}

DOF::~DOF() = default;

int64_t DOF::GetFirstEquation() {
    return firstequation;
}

void DOF::SetFirstEquation(int64_t first) {
    firstequation = first;
}

void DOF::SetNShapeStateOrder(int NShape, int NState, int Order) {
    nshape = NShape;
    nstate = NState;
    order = Order;
}

int DOF::GetNShape() const {
    return nshape;
}

int DOF::GetNState() const {
    return nstate;
}

int DOF::GetOrder() const {
    return order;
}

void DOF::Print(const CompMesh &mesh, std::ostream & out) {
    std::cout << "DOF Info:" << std::endl;
    std::cout << "NShape: " << nshape << std::endl;
    std::cout << "NState: " << nstate << std::endl;
    std::cout << "Order: " << order << std::endl;
}
