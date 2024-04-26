//Autor: Jonathan Martínez Pérez
//Fichero: nodoAVL.h
#pragma once

#include "nodoB.h"

template<typename Key>
class NodoAVL {
public:

    NodoAVL(const Key& dato) : dato(dato), izdo(nullptr), dcho(nullptr), bal(0) {}

    NodoAVL<Key>*& getIzdo() { return izdo; }
    NodoAVL<Key>*& getDcho() { return dcho; }
    Key getDato() const { return dato; }
    NodoAVL<Key>* getIzdo() const { return izdo; } 
    NodoAVL<Key>* getDcho() const { return dcho; }

    void setDcho(NodoAVL<Key>* nodo) { dcho = nodo; }
    void setIzdo(NodoAVL<Key>* nodo) { izdo = nodo; }
    
    int& getBal() { return bal; }
    void setBal(int bal) { this->bal = bal; }

private:
    Key dato; 
    NodoAVL<Key>* izdo;
    NodoAVL<Key>* dcho;
    int bal;
};