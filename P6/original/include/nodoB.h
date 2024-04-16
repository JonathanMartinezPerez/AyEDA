#pragma once

#include <iostream>

template<typename Key>
class NodoB {
public:
    NodoB(const Key& dato) : dato(dato), izdo(nullptr), dcho(nullptr) {}
    Key dato;
    NodoB* izdo;
    NodoB* dcho;
};