//Autor: Jonathan Martínez Pérez
//Fichero: usagetools.h
#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <chrono>

#include "nif.h"
#include "AB.h"
#include "ABB.h"
#include "ABE.h"
#include "AVL.h"


// Clase para parsear los argumentos de entrada y ejecutar la simulación
class Options {
public:
    Options(int argc, char* argv[]);
    void RunSimulation();
    void Usage() const;
    void Menu(AB<NIF>* arbol) const;
private:
    std::string initsystem;
    std::string filename;
    std::string ab;
    std::string trace;
    int quantity;
    bool hasQuantity = false;
    bool hasAb = false;
    bool hasInitSystem = false;
    bool hasFile = false;
    bool hasTrace = false;
    
};
