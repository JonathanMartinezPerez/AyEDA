//main.cc
#include "../include/function.h"
#include "../include/hash.h"
#include "../include/exploration.h"   
#include "../include/sequence.h"
#include "../include/nif.h"
#include "../include/usagetools.h"

#include <iostream>

int main(int argc, char* argv[]) {
    try {
        Options options = ParseArguments(argc, argv);

        // Definir la función de dispersión
        DispersionFunction<NIF>* dispersionFunction;
        if (options.dispersionFunction == "Module")
            dispersionFunction = new ModuleDispersion<NIF>(options.tableSize);
        else if (options.dispersionFunction == "Sum")
            dispersionFunction = new SumDispersion<NIF>(options.tableSize);
        else if (options.dispersionFunction == "Pseudorandom")
            dispersionFunction = new PseudorandomDispersion<NIF>(options.tableSize);
        else {
            std::cerr << "Función de dispersión no válida" << std::endl;
            return 1;
        }

        // Definir la función de exploración
        ExplorationFunction<NIF>* explorationFunction;
        if (options.explorationFunction == "Linear")
            explorationFunction = new LinearExploration<NIF>();
        else if (options.explorationFunction == "Quadratic")
            explorationFunction = new QuadraticExploration<NIF>();
        else if (options.explorationFunction == "DoubleHashing")
            explorationFunction = new DoubleHashingExploration<NIF>(*dispersionFunction);
        else if (options.explorationFunction == "Rehashing")
            explorationFunction = new RehashingExploration<NIF>(*dispersionFunction);
        else {
            std::cerr << "Función de exploración no válida" << std::endl;
            return 1;
        }

        // Crear la tabla hash
        HashTable<NIF> hashTable(options.tableSize, *dispersionFunction, *explorationFunction, options.blockSize);

        // Operaciones con la tabla hash (buscar, insertar, etc.)

        // Liberar la memoria de las funciones de dispersión y exploración
        delete dispersionFunction;
        delete explorationFunction;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        Usage();
        return 1;
    }

    return 0;
}