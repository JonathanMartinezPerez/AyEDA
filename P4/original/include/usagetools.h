//usagetools.h
#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

#include "nif.h"
#include "sequence.h"
#include "function.h"
#include "exploration.h"
#include "hash.h"

// Clase para parsear los argumentos de entrada y ejecutar la simulación
class Options {
public:
    Options(int argc, char* argv[]);
    void RunSimulation();
    void Usage() const;
    void Menu();
private:
    unsigned int tableSize;
    std::string dispersionFunction;
    std::string hashType;
    unsigned blockSize;
    std::string explorationFunction;
    HashTable<NIF>* hashTable;
    HashTable<NIF, DynamicSequence<NIF>>* hashTable_d;
};

extern DispersionFunction<NIF>* dispersionFunctionInstance;
extern ExplorationFunction<NIF>* explorationFunctionInstance;
