/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GeoElementTemplate.h"
#include "GeoMesh.h"
#include "Geom1d.h"
#include "GeomQuad.h"
#include "GeomTriangle.h"
#include "GeomTetrahedron.h"
#include "tpanic.h"

using namespace std;

template<class TGeom>
GeoElementTemplate<TGeom>::GeoElementTemplate(const VecInt &nodeindices, int materialid, GeoMesh *gmesh, int index) {
    gmesh->SetNumElements(index + 1);
    Geom.SetNodes(nodeindices);
    for (int side = 0; side < TGeom::nSides; side++) {
        Geom.SetNeighbour(side, GeoElementSide(this, side));
    }
    gmesh->SetElement(index, this);
}

template<class TGeom>
GeoElementTemplate<TGeom>::GeoElementTemplate(const GeoElementTemplate &copy) {
    Geom = copy.Geom;
}

template<class TGeom>
GeoElementTemplate<TGeom> &GeoElementTemplate<TGeom>::operator=(const GeoElementTemplate &copy) {
    Geom = copy.Geom;
    return *this;
}

template<class TGeom>
ElementType GeoElementTemplate<TGeom>::Type() {
    return TGeom::Type();
}

template<class TGeom>
void GeoElementTemplate<TGeom>::X(const VecDouble &xi, VecDouble &x) {
    int NNodes = this->NNodes();
    Matrix coord(3, NNodes);

    int i, j;
    for (i = 0; i < NNodes; i++) {
        int index = this->NodeIndex(i);
        GeoNode node = GMesh->Node(index);
        for (j = 0; j < 3; j++) {
            coord(j, i) = node.Coord(j);
        }
    }
    Geom.X(xi, coord, x);
}

template<class TGeom>
void GeoElementTemplate<TGeom>::GradX(const VecDouble &xi, VecDouble &x, Matrix &gradx) {
    int NNodes = this->NNodes();
    Matrix coord(3, NNodes);

    int i, j;
    for (i = 0; i < NNodes; i++) {
        int index = this->NodeIndex(i);
        GeoNode node = GMesh->Node(index);
        for (j = 0; j < 3; j++) {
            coord(j, i) = node.Coord(j);
        }
    }
    Geom.GradX(xi, coord, x, gradx);
}

template<class TGeom>
void GeoElementTemplate<TGeom>::Jacobian(const Matrix &gradx, Matrix &jac, Matrix &axes, double &detjac, Matrix &jacinv) {
    DebugStop();
}

template<class TGeom>
int GeoElementTemplate<TGeom>::WhichSide(VecInt &SideNodeIds) {
    DebugStop();
}

template<class TGeom>
void GeoElementTemplate<TGeom>::Print(std::ostream &out) {
    DebugStop();
}

template<class TGeom>
int GeoElementTemplate<TGeom>::SideIsUndefined(int side) {
    DebugStop();
}


template class GeoElementTemplate<Geom1d>;
template class GeoElementTemplate<GeomQuad>;
template class GeoElementTemplate<GeomTriangle>;
template class GeoElementTemplate<GeomTetrahedron>;
