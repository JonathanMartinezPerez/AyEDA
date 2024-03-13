#include <iostream>
#include <cstdlib>
#include "function.h"

// Clase para implementar las funciones de exploración
template <class Key>
class ExplorationFunction {
  public:
    virtual unsigned operator()(const Key&, unsigned i) const = 0; // i es el intento de exploración
    virtual ~ExplorationFunction() {}
};

// Clase para implementar la exploración lineal
template <class Key>
class LinearExploration : public ExplorationFunction<Key> {
  public:
    unsigned operator()(const Key& key, unsigned i) const override {
      return i;
    }
};

// Clase para implementar la exploración cuadrática
template <class Key> 
class QuadraticExploration : public ExplorationFunction<Key> {
  public:
    unsigned operator()(const Key& key, unsigned i) const override {
      return (i * i);
    }
};

// Clase para implementar la exploración doble
template <class Key>
class DoubleHashingExploration : public ExplorationFunction<Key> {
    public:
        DoubleHashingExploration(const DispersionFunction<Key>& f) : f_(f) {}
        unsigned operator()(const Key& key, unsigned i) const override {
            return (f_(key) * i);
        }
    private:
        DispersionFunction<Key> f_; // Función auxiliar f(k)
};

template <class Key>
class RehashingExploration : public ExplorationFunction<Key> {
  public:
    RehashingExploration(const DispersionFunction<Key>& f) : f_(f) {}
    unsigned operator()(const Key& key, unsigned i) const override {
      unsigned hashValue = f_(key);
      for (unsigned count = 0; count < i; count++) {
        hashValue = f_(hashValue);
      }
      return hashValue;
    }
  private:
    const DispersionFunction<Key>& f_; // Función auxiliar f(k)
};