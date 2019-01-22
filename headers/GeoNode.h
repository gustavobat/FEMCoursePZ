//
//  GeoNode.h
//  FEMCoursePZ
//
//  Created by Philippe Devloo on 16/04/18.
//

#ifndef GeoNode_h
#define GeoNode_h

#include "DataTypes.h"
#include "tpanic.h"

class GeoNode {

    // Vector with node coordinates
    VecDouble xco;
    
public:
    
    // Constructor of GeoNode
    GeoNode(): xco(0) {
        
    }
    
    // Constructor of GeoNode
    GeoNode(VecDouble &co) : xco(co) {
        if (co.size() > 3) {
            DebugStop();
        }
    }
    
    // Destructor of GeoNode
    ~GeoNode() {
        
    }
    
    // Copy constructor of GeoNode
    GeoNode(const GeoNode &copy) : xco(copy.xco) {
        
    }
    
    // Operator of copy
    GeoNode &operator=(const GeoNode &copy) {
        xco = copy.xco;
        return *this;
    }
    
    // Return the coordinates of the current node
    VecDouble Co() {
        return xco;
    }
    
    // Return i-th coordinate of the current node
    double Coord(int coo) {
        return xco[coo];
    }
    
    // Sets all coordinates into the current node
    void SetCo(const VecDouble &co) {
        if (co.size() > 3) {
            DebugStop();
        }

        xco = co;
    }
    
    // Function to print results
    void Print(std::ostream &out);
    
};
#endif /* GeoNode_h */