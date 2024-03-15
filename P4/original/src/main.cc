//main.cc
#include "../include/sequence.h"
#include "../include/function.h"
#include "../include/exploration.h"
#include "../include/hash.h"

#include <iostream>

int main() {
    // Crear objetos de dispersión y exploración
    ModuleDispersion<int> modulo(6);
    LinearExploration<int> linear;
    QuadraticExploration<int> quadratic;
    ModuleDispersion<int> moduloDouble(6);
    DoubleHashingExploration<int> doubleHashing(moduloDouble);
    ModuleDispersion<int> moduloRehash(6);
    RehashingExploration<int> rehashing(moduloRehash);

    // Crear una tabla de dispersión con staticSequence como contenedor
    HashTable<int, StaticSequence<int>> staticHashTable(10, modulo, linear, 5);

    // Insertar algunos elementos en la tabla de dispersión estática
    staticHashTable.insert(5);
    staticHashTable.insert(15);
    staticHashTable.insert(25);
    staticHashTable.insert(35);

    // Mostrar la tabla de dispersión estática
    std::cout << "Tabla de dispersión estática:" << std::endl;
    staticHashTable.display(std::cout);

    return 0;
}
