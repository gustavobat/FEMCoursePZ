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
        ek.Zero();
        ef.Zero();

        cel->CalcStiff(ek, ef);

        int nsides = cel->GetGeoElement()->NSides();

        VecInt DOFfirsteq(0);

        for (int64_t idofs = 0; idofs < nsides; idofs++) {
            int64_t dofindex = cel->GetDOFIndex(idofs);
            DOF dof = cmesh->GetDOF(dofindex);
            if (dof.GetNShape() > 0) {
                DOFfirsteq.push_back(dof.GetFirstEquation());
            }
        }

        for (int64_t idofs = 0; idofs < DOFfirsteq.size(); idofs++) {
            int64_t dofindexi = cel->GetDOFIndex(idofs);
            int64_t fei = DOFfirsteq[idofs];
            DOF dofi = cmesh->GetDOF(dofindexi);

            for (int64_t jdofs = 0; jdofs < DOFfirsteq.size(); jdofs++) {
                int64_t fej = DOFfirsteq[jdofs];
                int64_t dofindexj = cel->GetDOFIndex(jdofs);
                DOF dofj = cmesh->GetDOF(dofindexj);

                for (int64_t idim = 0; idim < dofi.GetNState() * dofi.GetNShape(); idim++) {
                    for (int64_t jdim = 0; jdim < dofj.GetNState() * dofj.GetNShape(); jdim++) {
                        globmat(fei + idim, fej + jdim) += ek(idofs * dofj.GetNState() + idim,
                                                              jdofs * dofj.GetNState() + jdim);
                    }
                }
            }

            for (int64_t idim = 0; idim < dofi.GetNState() * dofi.GetNShape(); idim++) {
                rhs(fei + idim, 0) += ef(idofs * dofi.GetNState() + idim, 0);
            }

        }
    }
    std::cout << "Assembly done!" << std::endl;
}
