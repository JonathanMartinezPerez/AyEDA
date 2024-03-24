#include <iostream>
#include <vector>
#include <random>

#include "sequence.h"
#include "sortmethod.h"
#include "nif.h"

int main() {
    // Tamaño del vector
    const int size = 10;

    // Crear una instancia de StaticSequence<NIF>
    StaticSequence<NIF> sequence;
    
    // Generar datos aleatorios de tipo NIF y insertarlos en la secuencia
    std::cout << "Generando NIFs aleatorios..." << std::endl;
    for (int i = 0; i < size; ++i) {
        NIF random_nif;
        sequence.insert(random_nif);
    }

    // Mostrar los datos generados
    std::cout << "Datos generados aleatoriamente:" << std::endl;
    const NIF* data = sequence.getData();
    for (unsigned i = 0; i < sequence.getSize(); ++i) {
        std::cout << data[i] << std::endl;
    }

    // Ordenar los datos usando el algoritmo de inserción
    Insertion<NIF> insertion_sort(sequence.getData());
    insertion_sort.Sort();

    // Mostrar los datos ordenados
    std::cout << "Datos ordenados:" << std::endl;
    const NIF* sorted_data = sequence.getData();
    for (unsigned i = 0; i < sequence.getSize(); ++i) {
        std::cout << sorted_data[i] << std::endl;
    }

    return 0;
}
