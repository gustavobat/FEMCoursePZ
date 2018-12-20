#include <iostream>
#include <fstream>
#include <math.h>
#include <TMatrix.h>

#include "IntRule1d.h"

int main () {

    for (int i = 0; i <= 5; i++) {

        IntRule1d intRuleTest(i);
        intRuleTest.Print(std::cout);
    }

    return 0;
}

