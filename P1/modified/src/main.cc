//Practica 1 : Implementación de un autómata celular unidimensional
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
    /*
    if (params.outputbyfile()) {
        std::string name = params.nameoutputf();
        std::ofstream out(name);

        std::streambuf *coutbuf = std::cout.rdbuf(); 
        std::cout.rdbuf(out.rdbuf()); 

        params.runSimulation(params);

        std::cout.rdbuf(coutbuf);
        out.close();
    } else {
        params.runSimulation(params);
    }
    */  
