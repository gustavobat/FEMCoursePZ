/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GeoElementSide.h"
#include "tpanic.h"

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
    fElement->SetNeighbour(fSide,neighbour);
}

bool GeoElementSide::IsNeighbour(const GeoElementSide &candidate) {
    if (*this == candidate) return true;
    GeoElementSide neigh = Neighbour();
    while((neigh == *this) == false) {
        if(neigh == candidate) return true;
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
    DebugStop();
}

bool GeoElementSide::DataConsistency(GeoElementSide &candidate) {
    std::cout << "Not implemented" << std::endl;
    DebugStop();
}
