//Autor: Jonathan Martínez Pérez
//Archivo: sortmethod.h
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "sortmethod.h"

// Implementación del algoritmo de ordenación por Inserción
template<class Key>
class Insertion : public SortMethod<Key> {
    public:
        Insertion(StaticSequence<Key> arr) : seq(arr) {}
        ~Insertion() = default;
        void Sort() override;
};

template<class Key>
void Insertion<Key>::Sort() {
    for (unsigned i = 1; i < this->size; ++i) {
        Key key = this->seq[i];
        int j = i - 1;
        while (j >= 0 && this->seq[j] > key) {
            this->seq[j + 1] = this->seq[j];
            --j;
        }
        this->seq[j + 1] = key;

        std::cout << "Iteración " << i - 1 << ": ";
        for (int num : this->seq) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}