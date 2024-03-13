#pragma once

#include <iostream>
#include <cstdlib>

class NIF {
  public:
    NIF() : value_(rand() % 100000000) {}
    NIF(long int val) : value_(val) {}
    bool operator==(const NIF& other) const { return value_==other.value_; }
    bool operator!=(const NIF& other) const { return !(*this == other); }
    operator long() const { return value_; }
  private:
    int value_; // DNI
};