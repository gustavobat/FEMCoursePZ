/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Geom1d.h"
#include "tpanic.h"

Geom1d::Geom1d() {
    fNodeIndices = {-1, -1, -1};
}

Geom1d::~Geom1d() {

}

Geom1d::Geom1d(const Geom1d &copy) {

    fNodeIndices = copy.fNodeIndices;

    for (auto i = 0; i < nSides; i++) {
        fNeighbours[i] = copy.fNeighbours[i];
    }
}

Geom1d& Geom1d::operator=(const Geom1d& copy) {

    fNodeIndices = copy.fNodeIndices;

    for (auto i = 0; i < nSides; i++) {
        fNeighbours[i] = copy.fNeighbours[i];
    }
    return *this;
}

void Geom1d::Shape(const VecDouble &xi, VecDouble &phi, Matrix &dphi) {
    phi[0] = (1.0 - xi[0]) / 2.;
    phi[1] = (1.0 + xi[0]) / 2.;
    dphi(0,0) = -0.5;
    dphi(0,1) = +0.5;
}

void Geom1d::X(const VecDouble &xi, Matrix &NodeCo, VecDouble &x) {
    DebugStop();
}

void Geom1d::GradX(const VecDouble &xi, Matrix &NodeCo, VecDouble &x, Matrix &gradx) {
    DebugStop();
}

void Geom1d::SetNodes(const VecInt &nodes) {

    if (nodes.size() > 2) {
        DebugStop();
    }

    fNodeIndices = nodes;
}

void Geom1d::GetNodes(VecInt &nodes) {
    nodes = fNodeIndices;
}

int Geom1d::NodeIndex(int node) {

    if (node < 0 || node > (nCorners - 1)) {
        DebugStop();
    }

    return fNodeIndices[node];
}

int Geom1d::NumNodes() {
    return nCorners;
}

GeoElementSide Geom1d::Neighbour(int side) {

    if (side < 0 || (side > nSides - 1)) {
        DebugStop();
    }

    return fNeighbours[side];
}

void Geom1d::SetNeighbour(int side, const GeoElementSide &neighbour) {

    if (side < 0 || (side > nSides - 1)) {
        DebugStop();
    }

    fNeighbours[side] = neighbour;
}
