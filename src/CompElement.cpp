/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CompElement.h"
#include "tpanic.h"

using namespace std;

CompElement::CompElement() {
}

CompElement::CompElement(int64_t ind, CompMesh *cmesh, GeoElement *geo) {
    compmesh = cmesh;
    geoel = geo;
    index = ind;
}

CompElement::CompElement(const CompElement &copy) {
    compmesh = copy.compmesh;
    geoel = copy.geoel;
    index = copy.index;
    intrule = copy.intrule;
    mat = copy.mat;
    compmesh->SetElement(index, this);
}

CompElement &CompElement::operator=(const CompElement &copy) {
    compmesh = copy.compmesh;
    geoel = copy.geoel;
    index = copy.index;
    intrule = copy.intrule;
    mat = copy.mat;
    compmesh->SetElement(index, this);
    return *this;
}

CompElement::~CompElement() = default;

CompElement *CompElement::Clone() const {
    return new CompElement(this);
}

MathStatement *CompElement::GetStatement() const {
    return mat;
}

void CompElement::SetStatement(MathStatement *statement) {
    mat = statement;
}

IntRule *CompElement::GetIntRule() const {
    return intrule;
}

void CompElement::SetIntRule(IntRule *irule) {
    intrule = irule;
}

void CompElement::SetIndex(int64_t ind) {
    index = ind;
}

GeoElement *CompElement::GetGeoElement() const {
    return geoel;
}

void CompElement::SetGeoElement(GeoElement *element) {
    geoel = element;
}

CompMesh *CompElement::GetCompMesh() const {
   return compmesh;
}

void CompElement::SetCompMesh(CompMesh *mesh) {
    compmesh = mesh;
}

void CompElement::InitializeIntPointData(IntPointData &data) const {

    const int nstate = mat->NState();
    const int nshape = this->NShapeFunctions();
    const int dim = this->Dimension();

    data.ksi.resize(3, 0.);
    data.x.resize(3, 0.);
    data.phi.resize(nshape, 0.);

    data.dphidksi.Resize(dim, nshape);
    data.dphidksi.Zero();

    data.gradx.Resize(3, 3);
    data.gradx.Zero();

    data.axes.Resize(dim, 3);
    data.axes.Zero();

    data.dphidx.Resize(dim, nshape);
    data.dphidx.Zero();

    data.weight = 0.;
    data.detjac = 0.;

    data.solution.resize(nshape*nstate, 0.);

    data.dsoldksi.Resize(dim, nshape*nstate);
    data.dsoldksi.Zero();

    data.dsoldx.Resize(dim, nshape*nstate);
    data.dsoldx.Zero();
}

void CompElement::ComputeRequiredData(IntPointData &data, VecDouble &intpoint) const {

    if (!geoel) DebugStop();

    this->InitializeIntPointData(data);

    geoel->X(intpoint, data.x);
    geoel->GradX(intpoint, data.x, data.gradx);

    int dim = this->Dimension();

    Matrix jac(dim, dim);
    Matrix jacinv(dim, dim);

    geoel->Jacobian(data.gradx, jac, data.axes, data.detjac, jacinv);
    this->ShapeFunctions(intpoint, data.phi, data.dphidksi);
    this->Convert2Axes(data.dphidksi, jacinv, data.dphidx);
}

void CompElement::Convert2Axes(const Matrix &dphi, const Matrix &jacinv, Matrix &dphidx) const {

    int nshape = this->NShapeFunctions();
    int dim = this->Dimension();

    for (int ieq = 0; ieq < nshape; ieq++) {
        for (int idim = 0; idim < dim; idim++) {
            for (int jdim = 0; jdim < dim; jdim++) {
                dphidx(idim, ieq) += jacinv.GetVal(jdim, idim) * dphi.GetVal(jdim, ieq);
            }
        }
    }
}

void CompElement::CalcStiff(Matrix &ek, Matrix &ef) const {

    if(!mat) DebugStop();

    IntPointData data;
    for(int i = 0; i < intrule->NPoints(); i++) {

        intrule->Point(i, data.ksi, data.weight);
        double weight = data.weight;
        this->ComputeRequiredData(data, data.ksi);
        weight *= fabs(data.detjac);
        mat->Contribute(data, weight, ek, ef);
    }
}

void CompElement::EvaluateError(std::function<void(const VecDouble &loc, VecDouble &val, Matrix &deriv) > fp, VecDouble &errors) const {
    DebugStop();
}

void CompElement::Solution(VecDouble &intpoint, int var, VecDouble &sol) const {
    DebugStop();
}
