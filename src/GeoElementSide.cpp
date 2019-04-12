/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GeoElementSide.h"
#include "GeoMesh.h"
#include "tpanic.h"
#include <algorithm>

GeoElementSide::GeoElementSide() {

}

GeoElementSide::GeoElementSide(const GeoElementSide &copy) {
    fElement = copy.fElement;
    fSide = copy.fSide;
}

GeoElementSide &GeoElementSide::operator=(const GeoElementSide &copy) {
    fElement = copy.fElement;
    fSide = copy.fSide;
    return *this;
}

GeoElementSide GeoElementSide::Neighbour() const {
    return fElement ? fElement->Neighbour(fSide) : GeoElementSide();
}

void GeoElementSide::SetNeighbour(const GeoElementSide &neighbour) {
    fElement->SetNeighbour(fSide, neighbour);
}

bool GeoElementSide::IsNeighbour(const GeoElementSide &candidate) {
    if (*this == candidate) return true;
    GeoElementSide neigh = Neighbour();
    while ((neigh == *this) == false) {
        if (neigh == candidate) return true;
        neigh = neigh.Neighbour();
    }
    return false;
}

void GeoElementSide::InsertConnectivity(GeoElementSide &candidate) {
    GeoElementSide myneigh = Neighbour();
    GeoElementSide neighneigh = candidate.Neighbour();

    if (IsNeighbour(candidate)) {
        return;
    }
    candidate.SetNeighbour(myneigh);
    SetNeighbour(neighneigh);
}

void GeoElementSide::AllNeighbours(std::vector<GeoElementSide> &allneigh) {
    GeoElementSide neigh = Neighbour();
    while (neigh != *this) {
        allneigh.push_back(neigh);
        neigh = neigh.Neighbour();
    }
}

void GeoElementSide::ComputeNeighbours(std::vector<GeoElementSide> &compneigh) {
    if (fSide < fElement->NCornerNodes()) {
        AllNeighbours(compneigh);
        return;
    }

    int nsnodes = fElement->NSideNodes(fSide);
    std::vector<GeoElementSide> GeoElSideSet;
    std::vector<std::vector<int>> GeoElSet;
    GeoElSet.resize(27);
    VecInt nodeIndexes(nsnodes);
    int in;
    for (in = 0; in < nsnodes; in++) {
        nodeIndexes[in] = fElement->NodeIndex(fElement->SideNodeIndex(fSide, in));
        int localNode = fElement->SideNodeIndex(fSide, in);
        GeoElSideSet.resize(0);

        GeoElementSide localSide(fElement, in);
        localSide.AllNeighbours(GeoElSideSet);

        int nel = GeoElSideSet.size();

        for (int el = 0; el < nel; el++) {
            GeoElSet[in].push_back(GeoElSideSet[el].Element()->GetIndex());
        }
        std::sort(GeoElSet[in].begin(), GeoElSet[in].end());
    }

    VecInt result;
    VecInt result_aux;
    switch (nsnodes) {
        case 1:
            result = GeoElSet[0];
            break;
        case 2:
            std::set_intersection(GeoElSet[0].begin(), GeoElSet[0].end(), GeoElSet[1].begin(), GeoElSet[1].end(),
                                  std::back_inserter(result));
            break;
        case 3:
            std::set_intersection(GeoElSet[0].begin(), GeoElSet[0].end(), GeoElSet[1].begin(), GeoElSet[1].end(),
                                  std::back_inserter(result_aux));
            std::set_intersection(result_aux.begin(), result_aux.end(), GeoElSet[2].begin(), GeoElSet[2].end(),
                                  std::back_inserter(result));
            break;
        case 4: {
            VecInt inter1, inter2;
            std::set_intersection(GeoElSet[0].begin(), GeoElSet[0].end(), GeoElSet[2].begin(), GeoElSet[2].end(),
                                  std::back_inserter(inter1));
            if (inter1.empty()) break;
            std::set_intersection(GeoElSet[1].begin(), GeoElSet[1].end(), GeoElSet[3].begin(), GeoElSet[3].end(),
                                  std::back_inserter(inter2));
            if (inter2.empty()) break;
            std::set_intersection(inter1.begin(), inter1.end(), inter2.begin(), inter2.end(),
                                  std::back_inserter(result));
            inter1.clear();
            inter2.clear();
        }
            break;
        default: {
            VecInt inter1, inter2;
            inter1 = GeoElSet[0];
            for (in = 0; in < nsnodes - 1; in++) {
                std::set_intersection(inter1.begin(), inter1.end(), GeoElSet[in + 1].begin(), GeoElSet[in + 1].end(),
                                      std::back_inserter(inter2));
                if (inter2.empty()) break;
                inter1 = inter2;
            }
            inter1.clear();
            inter2.clear();
            result = inter2;
        }
    }
    int el, nel = result.size();
    GeoMesh *geoMesh = fElement->GetMesh();
    for (el = 0; el < nel; el++) {
        GeoElement *gelResult = geoMesh->Element(result[el]);
        int whichSd = gelResult->WhichSide(nodeIndexes);
        if (whichSd > 0) {
            compneigh.push_back(GeoElementSide(gelResult, whichSd));
        }
    }
    GeoElSideSet.clear();
    GeoElSet.clear();
    nodeIndexes.clear();
    result.clear();
    result_aux.clear();
}

bool GeoElementSide::DataConsistency(GeoElementSide &candidate) {
    std::cout << "Not implemented" << std::endl;
    DebugStop();
}
