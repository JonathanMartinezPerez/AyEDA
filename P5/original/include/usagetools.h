//Autor: Jonathan Martínez Pérez
//Fichero: usagetools.h
#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

#include "nif.h"
#include "sequence.h"
#include "ordenation.h"
#include "library.h"


// Clase para parsear los argumentos de entrada y ejecutar la simulación
class Options {
public:
    Options(int argc, char* argv[]);
    void RunSimulation();
    void Usage() const;
private:
    unsigned tableSize;
    std::string ordenationFunction;
    std::string initsystem;
    std::string filename;
    std::string traces;
    bool hasTableSize = false;
    bool hasOrdenationFunction = false;
    bool hasInitSystem = false;
    bool hasFile = false;
    bool hasTraces = false;
    
};
