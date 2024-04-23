//Autor: Jonathan Martinez Pérez
//File: nodoB.h
#pragma once

#include <iostream>

// Clase NodoB
template<typename Key>
class NodoB {
public:
    NodoB() : izdo(nullptr), dcho(nullptr) {}
    NodoB(const Key& dato) : dato(dato), izdo(nullptr), dcho(nullptr) {}

    Key getDato() const { return dato; }
    NodoB* getIzdo() const { return izdo; }
    NodoB* getDcho() const { return dcho; }
    void setDato(const Key& dato) { this->dato = dato; }
    void setIzdo(NodoB* nodo) { izdo = nodo; }
    void setDcho(NodoB* nodo) { dcho = nodo; }

protected:
    Key dato;
    NodoB* izdo;
    NodoB* dcho;
};