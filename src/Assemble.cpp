/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <DOF.h>
#include "Assemble.h"
#include "tpanic.h"

Assemble::Assemble() {
    DebugStop();
}

Assemble::Assemble(CompMesh *mesh) {
    cmesh = mesh;
}

Assemble::Assemble(const Assemble &copy) {
    cmesh = copy.cmesh;
}

Assemble &Assemble::operator=(const Assemble &copy) {
    cmesh = copy.cmesh;
    return *this;
}

void Assemble::SetMesh(CompMesh *mesh) {
    cmesh = mesh;
}

int64_t Assemble::NEquations() {

    int64_t neq = 0;
    std::vector<DOF> dofvec;
    dofvec = cmesh->GetDOFVec();
    int64_t ndofs = dofvec.size();

    for (int64_t idofs = 0; idofs < ndofs; idofs++) {
        neq += dofvec[idofs].GetNShape() * dofvec[idofs].GetNState();
    }

    return neq;
}

void Assemble::OptimizeBandwidth() {
    DebugStop();
}

void Assemble::Compute(Matrix &globmat, Matrix &rhs) {

    int nelem = cmesh->GetElementVec().size();

    for (int i = 0; i < nelem; i++) {

        CompElement * cel = cmesh->GetElement(i);
        if (!cel) { continue; }

        int nshape = cel->NShapeFunctions();
        int nstate = cel->GetStatement()->NState();

        Matrix ek(nshape * nstate, nshape * nstate);
        Matrix ef(nshape * nstate, 1);

        cel->CalcStiff(ek, ef);

        

    }
}
