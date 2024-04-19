//Autor: Jonathan Martinez Pérez
//File: main.cc
#include <iostream>

#include "AB.h"
#include "ABB.h"
//#include "ABE.h"

int main() {

    //probar el insertar
    ABB<int> arbol;
    arbol.insertar(10);
    arbol.insertar(5);
    arbol.insertar(15);
    arbol.insertar(3);
    arbol.insertar(3);

    //probar el buscar
    std::cout << "Buscar 3: " << arbol.buscar(3) << std::endl;
    std::cout << "Buscar 15: " << arbol.buscar(15) << std::endl;
    std::cout << "Buscar 7: " << arbol.buscar(7) << std::endl;

    arbol.inorden();

    return 0;
}