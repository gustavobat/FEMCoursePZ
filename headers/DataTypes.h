//
//  IntRule.h
//  FEMCoursePZ
//
//  Created by Philippe Devloo on 7/30/15.
//

#ifndef __DATATYPES__
#define __DATATYPES__

#include <cmath>
#include <stdio.h>
#include <vector>
#include "TMatrix.h"

typedef TMatrix Matrix;
typedef std::vector<int> VecInt;
typedef std::vector<double> VecDouble;
typedef double REAL;

enum ElementType {

    /*0*/    EPoint,
    /*1*/    ELine,
    /*2*/    ETriangle,
    /*3*/    EQuadrilateral,
    /*4*/    ETetrahedron
};

#endif /* defined(__FEMCoursePZ__DATATYPES__) */
