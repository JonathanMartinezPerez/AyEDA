//Autor: Jonathan Martinez Pérez
//File: main.cc
#include <iostream>

#include "AB.h"
#include "ABB.h"
#include "ABE.h"
#include "AVL.h"
#include "nif.h"
//#include "usagetools.h"

int main(/*int argc, char* argv[]*/) { 

    //probar AVL
    AVL<int> arbolAVL;

    // Insertar elementos en el árbol AVL
    arbolAVL.insertar(10);
    arbolAVL.insertar(5);
    arbolAVL.insertar(15);
    arbolAVL.insertar(3);
    arbolAVL.insertar(7);
    arbolAVL.insertar(12);
    arbolAVL.insertar(20);

    // Mostrar el árbol AVL por niveles
    std::cout << "Árbol AVL por niveles:" << std::endl;


    return 0;
}