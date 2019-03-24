/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GeoElement.h"
#include "tpanic.h"

GeoElement::GeoElement() {
    MaterialId = -999;
    GMesh = nullptr;
    Index = -1;
}

GeoElement::GeoElement(int materialid, GeoMesh *mesh, int index) {
    MaterialId = materialid;
    GMesh = mesh;
    Index = index;
}

GeoElement::GeoElement(const GeoElement &copy) {
    MaterialId = copy.MaterialId;
    GMesh = copy.GMesh;
    Index = copy.Index;
}

GeoElement::~GeoElement() {
}

CompElement *GeoElement::CreateCompEl(CompMesh *mesh, int64_t index) {
    DebugStop();
}

void GeoElement::Print(std::ostream &out) {
    DebugStop();
}
