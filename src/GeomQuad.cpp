/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "GeomQuad.h"
#include "tpanic.h"

GeomQuad::GeomQuad() {
    DebugStop();
}

GeomQuad::~GeomQuad() {
}

GeomQuad::GeomQuad(const GeomQuad &copy) {
    DebugStop();
}

GeomQuad& GeomQuad::operator=(const GeomQuad& copy) {
    DebugStop();
}

void GeomQuad::Shape(const VecDouble &xi, VecDouble &phi, Matrix &dphi) {
    phi[0] = (1. - xi[0]) * (1. - xi[1]) / 4.;
    phi[1] = (1. + xi[0]) * (1. - xi[1]) / 4.;
    phi[2] = (1. + xi[0]) * (1. + xi[1]) / 4.;
    phi[3] = (1. - xi[0]) * (1. + xi[1]) / 4.;

    dphi(0, 0) = (+xi[1] - 1.) / 4.;
    dphi(0, 1) = (-xi[1] + 1.) / 4.;
    dphi(0, 2) = (+xi[1] + 1.) / 4.;
    dphi(0, 3) = (-xi[1] - 1.) / 4.;

    dphi(1, 0) = (+xi[0] - 1.) / 4.;
    dphi(1, 1) = (-xi[0] - 1.) / 4.;
    dphi(1, 2) = (+xi[0] + 1.) / 4.;
    dphi(1, 3) = (-xi[0] + 1.) / 4.;
}

void GeomQuad::X(const VecDouble &xi, Matrix &NodeCo, VecDouble &x) {
    DebugStop();
}

void GeomQuad::GradX(const VecDouble &xi, Matrix &NodeCo, VecDouble &x, Matrix &gradx) {
    DebugStop();
}

void GeomQuad::SetNodes(const VecInt &nodes) {
    DebugStop();
}

void GeomQuad::GetNodes(VecInt &nodes) {
    DebugStop();
}

int GeomQuad::NodeIndex(int node) {
    DebugStop();
}

int GeomQuad::NumNodes() {
    DebugStop();
}

GeoElementSide GeomQuad::Neighbour(int side) {
    DebugStop();
}

void GeomQuad::SetNeighbour(int side, const GeoElementSide &neighbour) {
    DebugStop();
}
