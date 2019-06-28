/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GeoElement.h"
#include "tpanic.h"

#include "CompElementTemplate.h"
#include "Shape1d.h"
#include "ShapeQuad.h"
#include "ShapeTriangle.h"
#include "ShapeTetrahedron.h"

GeoElement::GeoElement() {
    MaterialId = -999;
    GMesh = nullptr;
    Reference = nullptr;
    Index = -6;
}

GeoElement::GeoElement(int materialid, GeoMesh *mesh, int index) {
    MaterialId = materialid;
    GMesh = mesh;
    Reference = nullptr;
    Index = index;
}

GeoElement::GeoElement(const GeoElement &copy) {
    MaterialId = copy.MaterialId;
    GMesh = copy.GMesh;
    Reference = copy.Reference;
    Index = copy.Index;
}

GeoElement::~GeoElement() {
}

CompElement *GeoElement::CreateCompEl(CompMesh *mesh, int64_t index) {
    GeoElement *gel = this;

    switch (gel->Type()) {
        case ELine:
            return new CompElementTemplate<Shape1d> (index, mesh, gel);
        case EQuadrilateral:
            return new CompElementTemplate<ShapeQuad> (index, mesh, gel);
        case ETriangle:
            return new CompElementTemplate<ShapeTriangle> (index, mesh, gel);
        case ETetrahedron:
            return new CompElementTemplate<ShapeTetrahedron> (index, mesh, gel);
    }
}

void GeoElement::Print(std::ostream &out) {
    DebugStop();
}
