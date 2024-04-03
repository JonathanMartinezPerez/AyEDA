#include <iostream>
#include <vector>
#include <random>

#include "sequence.h"
#include "sortmethod.h"
#include "ordenation.h"


int main() {

    StaticSequence<int>* sequence;
    sequence = new StaticSequence<int>(10);
    
    std::vector<int> values = {1, 3, 5, 6, 10, 4, 3, 7, 8, 9};
    for (auto value : values) {
        sequence->insert(value);
    }
    std::cout << "Before sorting: ";
    for (int i = 0; i < sequence->getSize(); i++) {
        std::cout << (sequence->getData()[i]) << " ";
    }
    std::cout << std::endl;

    Heap<int> selection(sequence);

    selection.Sort();

    std::cout << "After sorting: ";
    for (int i = 0; i < sequence->getSize(); i++) {
        std::cout << (sequence->getData()[i]) << " ";
    }
    std::cout << std::endl;

    delete sequence;

    return 0;
}
