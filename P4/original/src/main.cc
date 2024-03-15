//main.cc
#include "../include/sequence.h"
#include "../include/function.h"
#include "../include/exploration.h"
#include "../include/hash.h"

#include <iostream>

int main() {
    ModuleDispersion<int> disp(100);
    QuadraticExploration<int> expl;
    HashTable<int, StaticSequence<int>> tabla(100, disp, expl, 3);
    int input;
    while (std::cin >> input) {
        if (input == 'q') {
            break;
        }
        std::cout << tabla.insert(input) << std::endl;
    }   

    tabla.display();
    return 0;
}
