//Autor: Jonathan Martínez Pérez
//Archivo: sortmethod.h
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "sequence.h"

// Clase base abstracta para los métodos de ordenación
template <class Key>
class SortMethod {
    public:
        SortMethod (StaticSequence<Key>* sequence) : sequence_(sequence) {}
        virtual void Sort() const = 0;
        virtual void printTraces() const = 0;

    protected:
        StaticSequence<Key>* sequence_;
};