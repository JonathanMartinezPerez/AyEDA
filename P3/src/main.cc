// main para probar el funcionamiento de position.h y .cc

#include <iostream>

#include "position.h"

int main() {
    PositionDim<2> p(2, 1, 2);
    std::cout << p[0] << " " << p[1] << std::endl;
    return 0;
}