/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <GeoMesh.h>
#include <Assemble.h>
#include <VTKGeoMesh.h>
#include "Analysis.h"
#include "tpanic.h"

using namespace std;

Analysis::Analysis() : cmesh(nullptr), Solution(), GlobalSystem(), RightHandSide() {
}

Analysis::Analysis(CompMesh *mesh) : Solution(), GlobalSystem(), RightHandSide() {
    SetMesh(mesh);
}

Analysis::Analysis(const Analysis &cp) {
    if (&cp != this) {
        cmesh = cp.cmesh;
        Solution = cp.Solution;
        GlobalSystem = cp.GlobalSystem;
        RightHandSide = cp.RightHandSide;
    }
}

Analysis &Analysis::operator=(const Analysis &cp) {
    if (&cp != this) {
        cmesh = cp.cmesh;
        Solution = cp.Solution;
        GlobalSystem = cp.GlobalSystem;
        RightHandSide = cp.RightHandSide;
    }
    return *this;
}

Analysis::~Analysis() = default;

void Analysis::SetMesh(CompMesh *mesh) {

    if (mesh == nullptr) DebugStop();
    cmesh = mesh;

}

CompMesh *Analysis::Mesh() const {
    return cmesh;
}

void Analysis::RunSimulation() {

    Assemble assemble(cmesh);
    int neq = assemble.NEquations();

    GlobalSystem.Resize(neq, neq);
    GlobalSystem.Zero();

    RightHandSide.Resize(neq, 1);
    RightHandSide.Zero();

    Solution.Resize(neq, 1);
    Solution.Zero();

    assemble.Compute(GlobalSystem, RightHandSide);
    GlobalSystem.Solve_LU(RightHandSide);

    VecDouble sol(neq, 0.);

    for (int64_t ieq = 0; ieq < neq; ieq++) {
        sol[ieq] = RightHandSide(ieq, 0);
        Solution(ieq, 0) = RightHandSide(ieq, 0);
    }

    cmesh->LoadSolution(sol);
}

void Analysis::PostProcessSolution(const std::string &filename, PostProcess &defPostProc) const {
    VTKGeoMesh::PrintSolVTK(cmesh, defPostProc, filename);
}

VecDouble Analysis::PostProcessError(std::ostream &out, PostProcess &defPostProc) const {
    DebugStop();
}

