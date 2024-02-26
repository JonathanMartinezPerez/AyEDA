//Practica 2 : Implementación de un autómata celular bidimensional
//Autor : <Jonathan Martínez Pérez>
//Correo : <alu0101254098@ull.edu.es>
//Archivo main.cc

#include <iostream>

#include "lattice.h"
#include "cell.h"
#include "programparameters.h"

int main(int argc, char* argv[]) {
  
    ProgramParameters params(argc, argv);

    params.runSimulation();

    std::cout << "Terminando..." << std::endl;

    return 0;
}
