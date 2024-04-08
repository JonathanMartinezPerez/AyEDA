//Autor: Jonathan Matínez Pérez
//Fichero: main.cc

#include <iostream>
#include <vector>
#include <random>

#include "sequence.h"
#include "sortmethod.h"
#include "ordenation.h"
#include "nif.h"

//Programa principal, parsea los argumentos y corre la simulación
int main() {

    wantTrace = false;
    // Crear secuencias con tamaños 100 y 1000
    StaticSequence<NIF>* sequence100 = new StaticSequence<NIF>(100);
    StaticSequence<NIF>* sequence1000 = new StaticSequence<NIF>(1000);

    for (unsigned i = 0; i < 100; i++) {
      NIF value;
      sequence100->insert(value);
    }

    for (unsigned i = 0; i < 1000; i++) {
      NIF value;
      sequence1000->insert(value);
    }

    // Crear objetos de ordenación
    Selection<NIF>* selection100 = new Selection<NIF>(sequence100);
    Selection<NIF>* selection1000 = new Selection<NIF>(sequence1000);
    Quick<NIF>* quick100 = new Quick<NIF>(sequence100);
    Quick<NIF>* quick1000 = new Quick<NIF>(sequence1000);

    // Ordenar las secuencias
    selection100->Sort();
    selection1000->Sort();
    quick100->Sort();
    quick1000->Sort();

    std::cout << "Comparaciones Selection 100: " << selection100->getComparisonCount() << std::endl;
    std::cout << "Comparaciones Selection 1000: " << selection1000->getComparisonCount() << std::endl;
    std::cout << "Comparaciones Quick 100: " << quick100->getComparisonCount() << std::endl;
    std::cout << "Comparaciones Quick 1000: " << quick1000->getComparisonCount() << std::endl;

    return 0;
}
