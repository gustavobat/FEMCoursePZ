/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GeomTriangle.h"
#include "tpanic.h"

GeomTriangle::GeomTriangle() {
    fNodeIndices = {-1, -1, -1};
}

GeomTriangle::~GeomTriangle() {
}

GeomTriangle::GeomTriangle(const GeomTriangle &copy) {
    fNodeIndices = copy.fNodeIndices;

    for (auto i = 0; i < nSides; i++) {
        fNeighbours[i] = copy.fNeighbours[i];
    }
}

GeomTriangle& GeomTriangle::operator=(const GeomTriangle& copy) {
    fNodeIndices = copy.fNodeIndices;

    for (auto i = 0; i < nSides; i++) {
        fNeighbours[i] = copy.fNeighbours[i];
    }
    return *this;
}

void GeomTriangle::Shape(const VecDouble& xi, VecDouble& phi, Matrix& dphi) {
    phi[0] = 1. - xi[0] - xi[1];
    phi[1] = xi[0];
    phi[2] = xi[1];

    dphi(0, 0) = -1.;
    dphi(0, 1) = 1.;
    dphi(0, 2) = 0.;

    dphi(1, 0) = -1.;
    dphi(1, 1) = 0.;
    dphi(1, 2) = 1.;
}

void GeomTriangle::X(const VecDouble &xi, Matrix &NodeCo, VecDouble &x) {
    DebugStop();
}

void GeomTriangle::GradX(const VecDouble &xi, Matrix &NodeCo, VecDouble &x, Matrix &gradx) {
    DebugStop();
}

void GeomTriangle::SetNodes(const VecInt &nodes) {
    if (nodes.size() != nCorners) {
        DebugStop();
    }

    fNodeIndices = nodes;
}

void GeomTriangle::GetNodes(VecInt &nodes) {
    nodes = fNodeIndices;
}

int GeomTriangle::NodeIndex(int node) {
    if (node < 0 || node > (nCorners - 1)) {
        DebugStop();
    }

    return fNodeIndices[node];
}

int GeomTriangle::NumNodes() {
    return nCorners;
}

GeoElementSide GeomTriangle::Neighbour(int side) {
    if (side < 0 || (side > nSides - 1)) {
        DebugStop();
    }

    return fNeighbours[side];
}

void GeomTriangle::SetNeighbour(int side, const GeoElementSide &neighbour) {
    if (side < 0 || (side > nSides - 1)) {
        DebugStop();
    }

    fNeighbours[side] = neighbour;
}
