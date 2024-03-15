//main.cc
#include "../include/sequence.h"
#include "../include/function.h"
#include "../include/exploration.h"


#include <iostream>

//main para probar que sequence y function funcionan
int main() {
    
    std::cout << "Ejemplo de uso de la clase DispersionFunction: \n";

    ModuleDispersion<int> modulo(10);
    std::cout << "Modulo: " << modulo(23) << std::endl;

    SumDispersion<std::vector<int>> suma(10);
    std::vector<int> key = {1, 2, 3};
    std::cout << "Suma: " << suma(key) << std::endl;

    PseudorandomDispersion<int> pseudo(10);
    std::cout << "Pseudoaleatoria: " << pseudo(42) << std::endl;

    std::cout << "Ejemplo de uso de la clase Exploracion: \n";

    LinearExploration<int> lineal;
    std::cout << "Lineal: " << lineal(23, 2) << std::endl;

    QuadraticExploration<int> cuadratica;
    std::cout << "Cuadratica: " << cuadratica(23, 2) << std::endl;

    ModuleDispersion<int> modulo2(10);
    DoubleHashingExploration<int> doble_(modulo2);

    std::cout << "Doble: " << doble_(23, 2) << std::endl;

    ModuleDispersion<int> modulo3(10);
    RehashingExploration<int> redis(modulo3);
    std::cout << "Redispersion: " << redis(23, 2) << std::endl;

    std::cout << "Ejemplo de uso de la clase Sequence: \n";

    DynamicSequence<int> array; 
    std::cout << "Insetar 1 y 2 en el array: \n";
    array.insert(1);
    array.insert(2);

    std::cout << "Array: ";
    array.print(std::cout);

    std::cout << "Buscar 1 en el array: " << array.search(3) << std::endl;
    std::cout << "------------------\n";

    
    StaticSequence<int> list(4);
    std::cout << "Insetar 1 y 2 en la lista: \n";
    list.insert(1);
    list.insert(2);

    std::cout << "List: ";
    list.print(std::cout);

    std::cout << "Buscar 1 en la lista: " << list.search(1) << std::endl;

    return 0;
}
