//Autor: Jonathan Martinez Pérez
//File: ABE.h
#pragma once

#include <iostream>

#include "AB.h"

// Clase ABE heredada de AB
template<typename Key>
class ABE : public AB<Key> {
public:
    ABE() : AB<Key>() {}

    virtual bool insertar(const Key& k) override;
    bool equilibrio(void);
    virtual bool buscar(const Key& k) const override;


private:
    bool insertarRama(NodoB<Key>* nodo, const Key& k);
    bool equilibrioRama(NodoB<Key>* nodo);
    bool buscarRama(NodoB<Key>* nodo, const Key& k) const;
};

template<typename Key>
bool ABE<Key>::equilibrio(void) {
    return equilibrioRama(this->raiz);
}

template<typename Key>
bool ABE<Key>::equilibrioRama(NodoB<Key>* nodo) {
    if(nodo == nullptr){return true;}

    int eq = tamRama(nodo->getIzdo()) - tamRama(nodo->getDcho());

    switch (eq){
        case -1:
        break;
        case 0:
        break;
        case 1: 
        return equilibrioRama(nodo->getIzdo()) && equilibrioRama(nodo->getDcho());
        default: return false;
    }
}

template<typename Key>
bool ABE<Key>::insertar(const Key& k) {
  if (!buscar(k)) {
    if (this->getRaiz() == nullptr) {
        this->setRaiz(new NodoB<Key> (k));
        std::cout << "Insertado: " << k << std::endl;   
        this->mostrarPorNiveles(std::cout);
    } else {
        insertarRama(this->getRaiz(), k);
    }
    return true;
    } else {
        return false;
    }
}

template<typename Key>
bool ABE<Key>::insertarRama(NodoB<Key>* nodo, const Key& k) {
    if (nodo == nullptr) {
        this->raiz = new NodoB<Key>(k);
        std::cout << "Insertado: " << k << std::endl;
        this->mostrarPorNiveles(std::cout);
        return true;
    }

    if (AB<Key>::tamRama(nodo->getIzdo()) <= AB<Key>::tamRama(nodo->getDcho())) {
        if (nodo->getIzdo() != nullptr) {
            return insertarRama(nodo->getIzdo(), k);
        } else {
            nodo->setIzdo(new NodoB<Key>(k)); 
            std::cout << "Insertado: " << k << std::endl;
            this->mostrarPorNiveles(std::cout);
            return true;
        }
    } else {
        if (nodo->getDcho() != nullptr) {
            return insertarRama(nodo->getDcho(), k);
        } else {
            nodo->setDcho(new NodoB<Key>(k));
            std::cout << "Insertado: " << k << std::endl;
            this->mostrarPorNiveles(std::cout);
            return true;
        }
    }
    return false;
}


template<typename Key>
bool ABE<Key>::buscar(const Key& k) const {
    return buscarRama(this->raiz, k);
}

template <class Key>
bool ABE<Key>::buscarRama(NodoB<Key>* nodo, const Key& k) const {
  if (!nodo) {
    return false;
  }
  if (k == nodo->getDato()) {
    return true;
  }
  if (k < nodo->getDato())
    return buscarRama(nodo->getIzdo(), k);
  return buscarRama(nodo->getDcho(), k);
}