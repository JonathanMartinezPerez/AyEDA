//function.h
#pragma once

#include <iostream>
#include <cstdlib>

// Clase para implementar las funciones de dispersión
template <class Key>
class DispersionFunction {
public:
    DispersionFunction(unsigned int size) : tableSize_(size) {}
    virtual unsigned operator()(const Key& key) const = 0;
    ~DispersionFunction() {}
    unsigned getTableSize() const { return tableSize_; }
protected:
    unsigned tableSize_;
};

// Clase para implementar la funcion con modulo
template <class Key>
class ModuleDispersion : public DispersionFunction<Key> {
public:
    ModuleDispersion(unsigned int size) : DispersionFunction<Key>(size) {}
    unsigned operator()(const Key& key) const override {
        return key % this->getTableSize();
    }
};

// Clase para implementar la funcion de dispersión con suma
template <class Key>
class SumDispersion : public DispersionFunction<Key> {
public:
    SumDispersion(unsigned int size) : DispersionFunction<Key>(size) {}
    unsigned operator()(const Key& key) const override {
        unsigned sum = 0;
        unsigned x = key;
        unsigned y;
        while (x > 0){ 
            y = x % 10;
            sum = sum + y;
            x = x / 10;
        }
        return sum % this->getTableSize();
    }
};

// Clase para implementar la funcion de dispersión con pseudoaleatorio
template <class Key>
class PseudorandomDispersion : public DispersionFunction<Key> {
public:
    PseudorandomDispersion(unsigned int size) : DispersionFunction<Key>(size) {}
    unsigned operator()(const Key& key) const override {
        srand(static_cast<unsigned>(key));
        return rand() % this->getTableSize();
    }
};
