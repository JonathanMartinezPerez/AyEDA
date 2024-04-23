#pragma once

#include "nodoB.h"

template<typename Key>
class NodoAVL : public NodoB {
    public:
        NodoAVL(const Key& datoAVL) : dato(datoAVL), izdo(nullptr), dcho(nullptr) {}
        ~NodoAVL() {}

        int getBal() const { return bal_; }
        void setBal(int bal) { bal_ = bal; }

    private:
        int bal_;
};