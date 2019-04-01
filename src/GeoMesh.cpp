/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <GeoElementSide.h>
#include "GeoMesh.h"
#include "tpanic.h"

GeoMesh::GeoMesh() {
    Reference = 0;
    fDim = -1;
}

GeoMesh::GeoMesh(const GeoMesh &copy) {
    Elements = copy.Elements;
    Nodes = copy.Nodes;
    Reference = copy.Reference;
    fDim = copy.fDim;;
}

GeoMesh &GeoMesh::operator=(const GeoMesh &copy) {
    Nodes = copy.Nodes;
    Elements = copy.Elements;
    Reference = copy.Reference;
    fDim = copy.fDim;
    return *this;
}

void GeoMesh::SetNumNodes(int nnodes) {
    Nodes.resize(nnodes);
}

void GeoMesh::SetNumElements(int numelements) {
    Elements.resize(numelements);
}

int GeoMesh::NumNodes() {
    return Nodes.size();
}

int GeoMesh::NumElements() {
    return Elements.size();
}

GeoNode &GeoMesh::Node(int node) {
    if (node < 0 || node >= this->NumNodes()) {
        std::cout << "Invalid node index." << std::endl;
        DebugStop();
    }
    return Nodes[node];
}

void GeoMesh::SetElement(int elindex, GeoElement *gel) {
    if (elindex < 0 || elindex >= this->NumElements()) {
        std::cout << "Element index out of bounds." << std::endl;
        DebugStop();
    }
    Elements[elindex] = gel;
}

GeoElement *GeoMesh::Element(int elindex) {
    if (elindex < 0 || elindex >= this->NumElements()) {
        std::cout << "Invalid element index." << std::endl;
        DebugStop();
    }
    return Elements[elindex];
}

void GeoMesh::BuildConnectivity() {

    int nelem = this->NumElements();
    int nnodes = this->NumNodes();

    std::vector<int> sideNum(nnodes, -1);
    std::vector<GeoElement*> neighNode(nnodes, nullptr);

    for (int elindex = 0; elindex < nelem; elindex++) {
        GeoElement *gel = Elements[elindex];

        int ncorners = gel->NCornerNodes();

        for (int icorner = 0; icorner < ncorners; icorner++) {
            int node = gel->NodeIndex(icorner);

            // Side not defined yet
            if (sideNum[node] == -1) {
                neighNode[node] = gel;
                sideNum[node] = icorner;
            }
            // Side already defined
            else {
                // Creates a new side
                GeoElementSide neigh(neighNode[node], sideNum[node]);
                GeoElementSide gelside(gel, icorner);
                GeoElementSide neighbour = gelside.Neighbour();

                if (neighbour.Element() == nullptr) {
                    DebugStop();
                }
                if (!gelside.IsNeighbour(neigh)) {
                    gelside.InsertConnectivity(neigh);
                }
            }
        }
    }

    for (int elindex = 0; elindex < nelem; elindex++) {
        GeoElement *gel = Elements[elindex];
        if (!gel) continue;
        int nsides = gel->NSides();

        for (int isides = 0; isides < nsides; isides++) {
            GeoElementSide gelside(gel, isides);
            std::vector<GeoElementSide> neighbours;
            gelside.ComputeNeighbours(neighbours);
            int nneighbours = neighbours.size();
            for (int ineighbours = 0; ineighbours < nneighbours; ineighbours++) {
                gelside.InsertConnectivity(neighbours[ineighbours]);
            }
        }
    }
}

void GeoMesh::Print(std::ostream &out) {
    out << "\n\t\tGEOMETRIC MESH INFORMATION\n\n";
    out << "Number of nodes:\t" << this->NumNodes() << std::endl;
    out << "Number of elements:\t" << this->NumElements() << std::endl;

    out << "\n\tNode Information" << std::endl;
    for (int i = 0; i < this->NumNodes(); i++) {
        out << "Node index: " << i << "\t\t";
        this->Node(i).Print(out);
    }

    out << "\n\tElement Information" << std::endl;
    for (int i = 0; i < this->NumElements(); i++) {
        out << "Element index:\t\t" << i << std::endl;
        this->Element(i)->Print(out);
        out << std::endl;
    }
}
