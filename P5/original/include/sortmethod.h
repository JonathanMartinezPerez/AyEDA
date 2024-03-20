#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// Clase base abstracta para los métodos de ordenación
template<class Key>
class SortMethod {
protected:
    unsigned size;
    std::vector<Key> seq
public:
    SortMethod(vector<Key> arr) : seq(arr), size(arr.size()) {}
    virtual void Sort() = 0;
};

