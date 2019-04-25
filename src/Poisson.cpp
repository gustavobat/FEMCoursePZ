/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Poisson.h"
#include "tpanic.h"
#include <string.h>

Poisson::Poisson() : permeability(), forceFunction(nullptr), SolutionExact(nullptr) {

}

Poisson::Poisson(int materialid, Matrix &perm) {
    permeability = perm;
    this->SetMatID(materialid);
    forceFunction = nullptr;
    SolutionExact = nullptr;
}

Poisson::Poisson(const Poisson &copy) : MathStatement(copy) {
    permeability = copy.permeability;
    forceFunction = copy.forceFunction;
    SolutionExact = copy.SolutionExact;
}

Poisson &Poisson::operator=(const Poisson &copy) {
    permeability = copy.permeability;
    forceFunction = copy.forceFunction;
    SolutionExact = copy.SolutionExact;
    return *this;
}

Poisson *Poisson::Clone() const {
    return new Poisson(*this);
}

Poisson::~Poisson() = default;

Matrix Poisson::GetPermeability() const {
    return permeability;
}

void Poisson::SetPermeability(const Matrix &perm) {
    permeability = perm;
}

int Poisson::NEvalErrors() const {
    return 3;
}

int Poisson::VariableIndex(const PostProcVar var) const {
    if (var == ENone) return ENone;
    if (var == ESol) return ESol;
    if (var == EDSol) return EDSol;
    if (var == EFlux) return EFlux;
    if (var == EForce) return EForce;
    if (var == ESolExact) return ESolExact;
    if (var == EDSolExact) return EDSolExact;

    std::cout << "Poisson::VariableIndex: wrong input var" << std::endl;
    DebugStop();
    return -1;
}

Poisson::PostProcVar Poisson::VariableIndex(const std::string &name) {
    if (!strcmp("Sol", name.c_str())) return ESol;
    if (!strcmp("DSol", name.c_str())) return EDSol;
    if (!strcmp("Flux", name.c_str())) return EFlux;
    if (!strcmp("Force", name.c_str())) return EForce;
    if (!strcmp("SolExact", name.c_str())) return ESolExact;
    if (!strcmp("DSolExact", name.c_str())) return EDSolExact;

    std::cout << "Poisson::VariableIndex : wrong input name" << std::endl;

    DebugStop();
}

int Poisson::NSolutionVariables(const PostProcVar var) {
    if (var == ESol) return this->NState();
    if (var == EDSol) return this->Dimension();
    if (var == EFlux) return this->Dimension();
    if (var == EForce) return this->NState();
    if (var == ESolExact) return this->NState();
    if (var == EDSolExact) return this->Dimension();

    std::cout << "Poisson::NSolutionVariables: wrong input var" << std::endl;

    DebugStop();
    return -1;
}

void Poisson::ContributeError(IntPointData &data, VecDouble &u_exact, Matrix &du_exact, VecDouble &errors) const {

    Matrix perm = GetPermeability();

    errors.resize(NEvalErrors(), 0.);

    VecDouble u = data.solution;

    Matrix dudaxes = data.dsoldx;
    Matrix dudx = data.dsoldx;
    Matrix axes = data.axes;
    this->Axes2XYZ(dudaxes, dudx, axes);

    // L2 norm
    errors[1] = (u[0] - u_exact[0]) * (u[0] - u_exact[0]);

    // H1 semi-norm
    errors[2] = 0.;
    for (int i = 0; i < du_exact.Rows(); i++) {
        errors[2] += (dudx(i, 0) - du_exact(i, 0)) * (dudx(i, 0) - du_exact(i, 0));
    }

    // Energy Norm
    errors[0] = errors[1] + errors[2];
}

void Poisson::Contribute(IntPointData &data, double weight, Matrix &EK, Matrix &EF) const {

    VecDouble &phi = data.phi;
    Matrix &dphi = data.dphidx;
    VecDouble &x = data.x;

    int phiRows = phi.size();

    Matrix perm = this->GetPermeability();

    // Implements Poisson equation
    for (int in = 0; in < phiRows; in++) {

        VecDouble force(NState(), 0.);
        if (forceFunction) {
            forceFunction(x, force);
        }

        for (int istate = 0; istate < NState(); istate++) {
            EF(in * NState() + istate, 0) += force[istate] * phi[in] * weight;
        }

        for (int jn = 0; jn < phiRows; jn++) {
            for (int idim = 0; idim < Dimension(); idim++) {
                for (int istate = 0; istate < NState(); istate++) {
                    EK(in * NState() + istate, jn * NState() + istate) +=
                            perm(idim, idim) * dphi(idim, in) * dphi(idim, jn) * weight;
                }
            }
        }
    }

#ifdef DEBUG
    std::cout << "EK:\n";
    EK.Print(std::cout);
    std::cout << "EF:\n";
    EF.Print(std::cout);
#endif

}

void Poisson::PostProcessSolution(const IntPointData &data, const int varId, VecDouble &result) const {

    VecDouble u = data.solution;
    Matrix du = data.dsoldx;

    int nstate = this->NState();

    switch (varId) {
        // ESol
        case 1: {
            result = u;
        }
            break;

            // EDSol
        case 2: {
            result.resize(du.Rows() * du.Cols());
            for (int i = 0; i < du.Rows(); i++) {
                for (int j = 0; j < du.Cols(); j++) {
                    result[i * du.Cols() + j] = du(i, j);
                }
            }
        }
            break;

            // EFlux
        case 3: {

        }
            break;

            // EForce
        case 4: {
            result.resize(nstate);
            VecDouble result(nstate);
            this->forceFunction(data.x, result);
        }
            break;

            // ESolExact
        case 5: {
            result.resize(nstate);
            VecDouble solint(nstate);
            Matrix dsol(nstate, nstate);
            this->SolutionExact(data.x, result, dsol);
        }
            break;

            // EDSolExact
        case 6: {
            result.resize(du.Rows() * du.Cols());
            VecDouble solexact(nstate);
            Matrix dsolexact(nstate, nstate);
            this->SolutionExact(data.x, solexact, dsolexact);

            for (int i = 0; i < du.Rows(); i++) {
                for (int j = 0; j < du.Cols(); j++) {
                    result[i * du.Cols() + j] = dsolexact(i, j);
                }
            }
        }
            break;

        default: {
            std::cout << "Poisson::PostProcessSolution no variable associated with given index." << std::endl;
            DebugStop();
        }
    }
}

double Poisson::Inner(Matrix &S, Matrix &T) const {
    DebugStop();
    return -666.;
}
