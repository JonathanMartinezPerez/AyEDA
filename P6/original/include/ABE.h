//Autor: Jonathan Martinez Pérez
//File: ABE.h
#pragma once

#include <iostream>

#include "AB.h"

template<typename Key>
class ABE : public AB<Key> {
public:
    ABE() : AB<Key>() {}

    virtual bool insertar(const Key& k) override;
    //virtual bool buscar(const Key& k) const override;
    const int tamRama(NodoB<Key>* nodo) const;
    const bool equilibrioRama(NodoB<Key>*& nodo);

private:
    bool insertarRama(NodoB<Key>*& nodo, const Key& k);
    //bool buscarRama(NodoB<Key>* nodo, const Key& k) const;
};

template<typename Key>
bool ABE<Key>::insertar(const Key& k) {
    return insertarRama(this->raiz, k);
}

template<typename Key>
const bool ABE<Key>::equilibrioRama(NodoB<Key>*& nodo) {
    //verificar si existe raiz si no insertar y devolver true
    if (nodo == nullptr) {
        return true;
    }
    //creamos un nodo auxiliar para recorrer el arbol
    NodoB<Key>* aux = nodo;

    while(aux != nullptr) {
        int eq = tamRama(aux->getIzdo()) - tamRama(aux->getDcho());
        switch (eq){
            case 1:
            case 0:
            case -1:
            return  equilibrioRama(nodo->getIzdo()) && 
            equilibrioRama(nodo->getDcho());
            default: return false;

        }

    } 
    return false;  
}

template<typename Key>
const int ABE<Key>::tamRama(NodoB<Key>* nodo) const {
    if (nodo == nullptr) {
        return 0;
    } else {
        return 1 + tamRama(nodo->getIzdo()) + tamRama(nodo->getDcho());
    }
}
