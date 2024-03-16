//main.cc
#include "../include/sequence.h"
#include "../include/function.h"
#include "../include/exploration.h"
#include "../include/hash.h"

#include <iostream>

#include <iostream>
#include <string> // Incluir la cabecera para utilizar std::string
#include "../include/sequence.h"
#include "../include/function.h"
#include "../include/exploration.h"
#include "../include/hash.h"
#include "../include/nif.h"

int main() {
    SumDispersion<int> disp(100);
    QuadraticExploration<int> expl;
    HashTable<int, StaticSequence<int>> tabla(100, disp, expl, 3);
    //HashTable<int, DynamicSequence<int>> tabla2(100, disp);
    
    std::string input; // Cambiar el tipo de input a std::string
    
    while (std::cin >> input) {
        if (input == "q") { // Comparar con un string en lugar de un carácter
            break;
        }
        // Convertir el string a un entero utilizando std::stoi
        int value = std::stoi(input);
        std::cout << tabla.insert(value) << std::endl;
        //std::cout << tabla2.insert(input) << std::endl;
    }   

    std::cout << "¿Qué números quieres buscar?" << std::endl;
    while (std::cin >> input) {
        if (input == "q") { // Comparar con un string en lugar de un carácter
            break;
        }
        // Convertir el string a un entero utilizando std::stoi
        int value = std::stoi(input);
        std::cout << tabla.search(value) << std::endl;
        //std::cout << tabla2.search(input) << std::endl;
    }
    tabla.display();
    //tabla2.display();

    return 0;
}

