//Autor: Jonathan Martinez Pérez
//File: main.cc
#include <iostream>

#include "AB.h"
#include "ABB.h"
#include "ABE.h"
#include "nif.h"

int main() { 

    //probar el insertar
    ABE<NIF> arbol;
    arbol.insertar(10);
    arbol.insertar(5);
    arbol.insertar(15);
    arbol.insertar(3);
    arbol.insertar(3);

    arbol.inorden();

    return 0;
}