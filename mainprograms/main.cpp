#include <iostream>
#include <fstream>
#include <cmath>
#include <functional>
#include <string.h>

#include "VTKGeoMesh.h"

#include "GeoMesh.h"
#include "Geom1d.h"
#include "GeomQuad.h"
#include "GeomTriangle.h"
#include "GeomTetrahedron.h"
#include "GeoElementTemplate.h"

#include "MathStatement.h"
#include "L2Projection.h"
#include "Poisson.h"

#include "PostProcess.h"
#include "PostProcessTemplate.h"

using namespace std;

GeoMesh *QuadGeoMesh(int nnodes_x, int nnodes_y, double l);

void QuadrilateralMeshTest(int pOrder);

int main() {
    QuadrilateralMeshTest(1);
    return 0;
}

GeoMesh *QuadGeoMesh(int nnodes_x, int nnodes_y, double l) {
    int64_t nnodes = nnodes_x*nnodes_y;
    int64_t nelem = (nnodes_x - 1) * (nnodes_y - 1);

    GeoMesh *gmesh = new GeoMesh;

    gmesh->SetDimension(2);
    gmesh->SetNumNodes(nnodes);

    // Cria os nos da malha
    VecDouble coord(3, 0.);
    int64_t nodeid;
    for (int i = 0; i < nnodes_y; i++) {
        for (int j = 0; j < nnodes_x; j++) {
            nodeid = i * nnodes_x + j;
            coord[0] = (j) * l / (nnodes_x - 1);
            coord[1] = (i) * l / (nnodes_y - 1);
            gmesh->Node(nodeid).SetCo(coord);
        }
    }

    // Cria os elementos
    VecInt TopolQuad(4, 0);
    for (int i = 0; i < (nnodes_x - 1); i++) {
        for (int j = 0; j < (nnodes_y - 1); j++) {

            int index = i * (nnodes_y - 1) + j;
            TopolQuad[0] = i * nnodes_y + j;
            TopolQuad[1] = TopolQuad[0] + 1;
            TopolQuad[2] = TopolQuad[0]+(nnodes_y) + 1;
            TopolQuad[3] = TopolQuad[0]+(nnodes_y);

            int matid = 1;
            GeoElement *gel = new GeoElementTemplate<GeomQuad> (TopolQuad, matid, gmesh, index);
        }
    }

    VecInt topolLine(2, 0);
    Matrix co(2, 4, 0);
    int64_t id = nelem;

    int bc0 = -1;
    int bc1 = -2;
    int bc2 = -3;
    int bc3 = -4;

    //Condicoes de contorno
    for (int64_t iel = 0; iel < nelem; iel++) {

        //Indice do no de cada corner do elemento
        int ncorners = gmesh->Element(iel)->NCornerNodes();
        for (int i = 0; i < ncorners; i++) {
            TopolQuad[i] = gmesh->Element(iel)->NodeIndex(i);
        }

        // Coordenadas x e y de cada corner do elemento
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < ncorners; j++) {
                co(i, j) = gmesh->Node(TopolQuad[j]).Co()[i];
            }
        }

        // Condicao de contorno inferior
        if (co(1, 0) == 0 && co(1, 1) == 0) {
            topolLine[0] = TopolQuad[0];
            topolLine[1] = TopolQuad[1];
            GeoElement *gel = new GeoElementTemplate<Geom1d> (topolLine, bc0, gmesh, id);
            id++;
        }
        // Condicao de contorno da direita
        if (co(0, 1) == l && co(0, 2) == l) {
            topolLine[0] = TopolQuad[1];
            topolLine[1] = TopolQuad[2];
            GeoElement *gel = new GeoElementTemplate<Geom1d> (topolLine, bc1, gmesh, id);
            id++;
        }
        // Condicao de contorno superior
        if (co(1, 2) == l && co(1, 3) == l) {
            topolLine[0] = TopolQuad[2];
            topolLine[1] = TopolQuad[3];
            GeoElement *gel = new GeoElementTemplate<Geom1d> (topolLine, bc2, gmesh, id);
            id++;
        }

        // Condicao de contorno da esquerda
        if (co(0, 0) == 0 && co(0, 3) == 0) {
            topolLine[0] = TopolQuad[0];
            topolLine[1] = TopolQuad[3];
            GeoElement *gel = new GeoElementTemplate<Geom1d> (topolLine, bc3, gmesh, id);
            id++;
        }
    }
    gmesh->BuildConnectivity();

    coord.clear();
    TopolQuad.clear();
    topolLine.clear();

    return gmesh;
}

void QuadrilateralMeshTest(int pOrder) {
    string filename;
    ofstream fout;
    if (pOrder == 1) {
        fout.open("Quadrilateral-Linear.txt");
        filename = "Quadrilateral-Linear.vtk";
    } else if (pOrder == 2) {
        fout.open("Quadrilateral-Quadratic.txt");
        filename = "Quadrilateral-Quadratic.vtk";
    } else {
        cout << "Not implemented for this order!" << endl;
        DebugStop();
    }

    for (int i = 1; i < 2; i++) {
        int ndiv;
        ndiv = pow(2, i);
        double l = 1;

        fout << "-------------------------------------------" << std::endl;
        fout << "Number of elements: " << ndiv << "x" << ndiv << std::endl;
        cout << "\nNumber of elements: " << ndiv << "x" << ndiv << std::endl;

        GeoMesh *gmesh = QuadGeoMesh(ndiv + 1, ndiv + 1, l);

        VTKGeoMesh * testevtk = new VTKGeoMesh();
        testevtk->PrintGMeshVTK(gmesh, "teste.vtk");
    }
}

