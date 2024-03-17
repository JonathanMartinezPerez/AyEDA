//Autor: Jonathan Martínez Pérez
//Fichero: nif.h
#pragma once

#include <iostream>
#include <cstdlib>

// Clase para implementar el tipo de dato NIF
class NIF {
  public:
    NIF() : value_(rand() % 100000000) {}
    NIF(long int val) : value_(val) {}
    bool operator==(const NIF& other) const { return value_==other.value_; }
    bool operator!=(const NIF& other) const { return !(*this == other); }
    operator long() const { return value_; }
    friend std::istream& operator>>(std::istream& input, NIF& nif) {
        long int value;
        input >> value;
        nif = NIF(value);
        return input;
    }
  private:
    long int value_;
};

