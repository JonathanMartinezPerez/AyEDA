//Autor: Jonathan Matínez Pérez
//Fichero: main.cc

#include <iostream>
#include <vector>
#include <random>

#include "sequence.h"
#include "sortmethod.h"
#include "ordenation.h"
#include "nif.h"
#include "usagetools.h"

//Programa principal, parsea los argumentos y corre la simulación
int main(int argc, char *argv[]) {

    Options options(argc, argv);
    options.RunSimulation();

    return 0;
}
