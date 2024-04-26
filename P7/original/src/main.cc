//Autor: Jonathan Martinez Pérez
//File: main.cc
#include <iostream>

#include "AB.h"
#include "ABB.h"
#include "ABE.h"
#include "nif.h"
#include "usagetools.h"
#include "AVL.h"

int main(/*int argc, char* argv[]*/) { 

    //Options options(argc, argv);
    //options.RunSimulation();
    AB<int>* avl = new AVL<int>();

    avl->insertar(10);
    avl->insertar(5);

    return 0;
}