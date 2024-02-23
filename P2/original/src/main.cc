//Practica 2 : Implementación de un autómata celular bidimensional
//Autor : <Jonathan Martínez Pérez>
//Correo : <alu0101254098@ull.edu.es>
//Archivo main.cc

#include <iostream>

#include "lattice.h"
#include "cell.h"
#include "programparameters.h"

int main() {
  
    /*ProgramParameters params(argc, argv);

    params.runSimulation();

    std::cout << "Terminando..." << std::endl;*/

    Lattice lattice(10, 10, PERIODIC);

    lattice.ShowIterations();

    return 0;
}
