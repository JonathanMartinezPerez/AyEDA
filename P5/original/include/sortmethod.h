//Autor: Jonathan Martínez Pérez
//Archivo: sortmethod.h
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "sequence.h"

// Clase base abstracta para los métodos de ordenación
template<class Key>
class SortMethod {
    public:
        SortMethod() {}
        virtual ~SortMethod() = default;
        virtual void Sort() = 0;    
    protected:
        std::vector<Key>& seq;
        unsigned size;
};