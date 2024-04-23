//Autor: Jonathan Martinez Pérez
//File: main.cc
#include <iostream>

#include "AB.h"
#include "ABB.h"
#include "ABE.h"
#include "nif.h"
#include "usagetools.h"

int main(int argc, char* argv[]) { 

    Options options(argc, argv);
    options.RunSimulation();

    return 0;
}