#include <iostream>
#include "nif.h" // Incluir el archivo de encabezado para el tipo de dato NIF
#include "sequence.h"
#include "function.h"
#include "exploration.h"
#include "hash.h"

int main() {
    // Crear un objeto de dispersión y una función de exploración
    ModuleDispersion<NIF> disp(100);
    LinearExploration<NIF> expl;

    // Crear la tabla hash con el tipo de dato NIF y una secuencia estática
    HashTable<NIF, StaticSequence<NIF>> tabla(100, disp, expl, 3);

    // Variables para la entrada de usuario
    long int input;
    char input_char;

    // Bucle para insertar valores en la tabla hash
    std::cout << "Inserte valores NIF (o 'q' para salir):" << std::endl;
    while (std::cin >> input >> input_char) {
        if (input_char == 'q') {
            break;
        }
        NIF value(input);
        std::cout << tabla.insert(value) << std::endl;
    }

    // Bucle para buscar valores en la tabla hash
    std::cout << "Ingrese valores NIF para buscar (o 'q' para salir):" << std::endl;
    while (std::cin >> input >> input_char) {
        if (input_char == 'q') {
            break;
        }
        NIF value(input);
        std::cout << tabla.search(value) << std::endl;
    }

    // Mostrar contenido de la tabla hash
    std::cout << "Contenido de la tabla hash:" << std::endl;
    tabla.display();

    return 0;
}
