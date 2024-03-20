//Autor: Jonathan Martínez Pérez
//Archivo: sortmethod.h
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "sortmethod.h"

// Implementación del algoritmo de ordenación por seleccion
template<class Key>
class Selection : public SortMethod<Key> {
    public:
        Selection(std::vector<Key>& arr) : SortMethod<Key>(arr) {}
        ~Selection() = default;
        void Sort() override;
};

template<class Key>
void Selection<Key>::Sort() {
    for (unsigned i = 0; i < this->size - 1; ++i) {
        unsigned min = i;
        for (unsigned j = i + 1; j < this->size; ++j) {
            if (this->seq[j] < this->seq[min]) {
                min = j;
            }
        }
        std::swap(this->seq[i], this->seq[min]);
        
        std::cout << "Iteración " << i << ": ";
        for (int num : this->seq) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}