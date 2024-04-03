#include <iostream>
#include <vector>
#include <random>

#include "sequence.h"


int main() {
    StaticSequence<int> sequence(10);
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (auto value : values) {
        sequence.insert(value);
    }
    std::cout << "Before sorting: ";
    for (unsigned i = 0; i < sequence.getData().size(); i++) {
        std::cout << sequence[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
