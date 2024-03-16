//main.cc
#include "../include/sequence.h"
#include "../include/function.h"
#include "../include/exploration.h"
#include "../include/hash.h"

#include <iostream>

int main() {

    SumDispersion<int> disp(100);
    QuadraticExploration<int> expl;
    HashTable<int, StaticSequence<int>> tabla(100, disp, expl, 3);
    HashTable<int, DynamicSequence<int>> tabla2(100, disp);
    int input;
    while (std::cin >> input) {
        if (input == 'q') {
            break;
        }
        std::cout << tabla.insert(input) << std::endl;
        std::cout << tabla2.insert(input) << std::endl;
    }   

    tabla.display();
    tabla2.display();

    return 0;
}
