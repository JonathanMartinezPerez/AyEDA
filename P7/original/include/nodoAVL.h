#pragma once

#include "nodoB.h"

template<typename Key>
class NodoAVL : public NodoB<Key> {
public:
    NodoAVL(const Key& datoAVL) : NodoB<Key>(datoAVL), bal_(0) {}

    ~NodoAVL() {}
    NodoAVL*& getIzdo() { return this->izdo; }
    NodoAVL*& getDcho() { return this->dcho; }
    int& getBal() { return bal_; }
    void setBal(int bal) { bal_ = bal; }

private:
    int bal_;
    NodoAVL* dcho;
    NodoAVL* izdo;
};