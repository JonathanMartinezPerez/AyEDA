//Autor: Jonathan Martinez Pérez
//File: ABB.h
#pragma once

#include <iostream>

#include "AB.h"

// Clase ABB heredada de AB
template<typename Key>
class ABB : public AB<Key> {
public:
    ABB() : AB<Key>() {}

    virtual bool insertar(const Key& k) override;
    virtual bool buscar(const Key& k) const override;

private:
    bool insertarRama(NodoB<Key>*& nodo, const Key& k);
    bool buscarRama(NodoB<Key>* nodo, const Key& k) const;
};

// Método insertar para insertar un nodo en el árbol llamando a insertarRama
template<typename Key>
bool ABB<Key>::insertar(const Key& k) {
    return insertarRama(this->raiz, k);
}

// Método insertarRama para insertar un nodo en el árbol
template<typename Key>
bool ABB<Key>::insertarRama(NodoB<Key>*& nodo, const Key& k) {
    //verificar si existe raiz si no insertar y devolver true
    if (nodo == nullptr) {
        nodo = new NodoB<Key>(k);
        std::cout << "Insertado: " << k << std::endl;
        this->mostrarPorNiveles(std::cout);
        return true;
    }
    //creamos un nodo auxiliar para recorrer el arbol
    NodoB<Key>* aux = nodo;
    while(aux != nullptr) {
        //si el dato es menor que el dato del nodo actual
        if (k < aux->getDato()) {
            //si el nodo izquierdo es nulo insertamos el nodo
            if (aux->getIzdo() == nullptr) {
                aux->setIzdo(new NodoB<Key>(k));
                std::cout << "Insertado: " << k << std::endl;
                this->mostrarPorNiveles(std::cout);
                return true;
            }
            //si no seguimos recorriendo el arbol
            aux = aux->getIzdo();
        } else if (k > aux->getDato()) {
            //si el nodo derecho es nulo insertamos el nodo
            if (aux->getDcho() == nullptr) {
                aux->setDcho(new NodoB<Key>(k));
                std::cout << "Insertado: " << k << std::endl;
                this->mostrarPorNiveles(std::cout);
                return true;
            }
            //si no seguimos recorriendo el arbol
            aux = aux->getDcho();
        } else {
            //si el dato ya existe en el arbol
            std::cout << "El dato: " << k << " ya existe en el arbol" << std::endl;
            return false;
        }
    } 
    return false;  
}

// Método buscar para buscar un nodo en el árbol llamando a buscarRama
template<typename Key>
bool ABB<Key>::buscar(const Key& k) const {
    return buscarRama(this->raiz, k);
}

// Método buscarRama para buscar un nodo en el árbol
template <class Key>
bool ABB<Key>::buscarRama(NodoB<Key>* nodo, const Key& k) const {
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