//Autor: Jonathan Martinez Pérez
//File: AB.h
#pragma once

#include <iostream>
#include <queue>
#include <utility>
#include "nodoB.h"

template<typename Key>
class AVL;

// Clase abstracta AB
template<typename Key>
class AB {
public:
    AB();
    ~AB();

    virtual bool insertar(const Key& k) = 0;
    virtual bool buscar(const Key& k) const = 0;
    int tam(void);

    NodoB<Key>* getRaiz() const { return raiz; }
    void setRaiz(NodoB<Key>* nodo) { raiz = nodo; }

    virtual void inorden() const;

    friend class AVL<Key>;

protected:
    NodoB<Key>* raiz;

    void limpiar(NodoB<Key>* nodo);
    int tamRama(NodoB<Key>* nodo);
    void inordenRecursivo(NodoB<Key>* nodo) const;
    void mostrarPorNiveles(std::ostream& os) const;
};

// Constructor de la clase AB
template<typename Key>
AB<Key>::AB() : raiz(nullptr) {};

// Destructor de la clase AB
template<typename Key>
AB<Key>::~AB() {
    limpiar(raiz);
}

// Método limpiar para el destructor
template<typename Key>
void AB<Key>::limpiar(NodoB<Key>* nodo) {
    if (nodo != nullptr) {
        limpiar(nodo->getIzdo());
        limpiar(nodo->getDcho());
        delete nodo;
    }
}

// Método inorden para recorrer el árbol
template<typename Key>
void AB<Key>::inorden() const {
    inordenRecursivo(raiz);
    std::cout << std::endl;
}

// Método inorden recursivo
template<typename Key>
void AB<Key>::inordenRecursivo(NodoB<Key>* nodo) const {
    if (nodo != nullptr) {
        inordenRecursivo(nodo->getIzdo());
        std::cout << nodo->getDato() << " ";
        inordenRecursivo(nodo->getDcho());
    }
}

// Método tam para obtener el tamaño del árbol
template<typename Key>
int AB<Key>::tam(void) {
    return tamRama(raiz);
}

// Método tamRama para obtener el tamaño de una rama
template<typename Key>
int AB<Key>::tamRama(NodoB<Key>* nodo) {
    if (nodo == nullptr) {
        return 0;
    } else {
        return 1 + tamRama(nodo->getIzdo()) + tamRama(nodo->getDcho());
    }
}

// Método mostrarPorNiveles para mostrar el árbol por niveles
template<typename Key>
void AB<Key>::mostrarPorNiveles(std::ostream& os) const {
  std::queue<std::pair<NodoB<Key>*,int>> Q;
  NodoB<Key> *nodo;
  int nivel, Nivel_actual = 0;
  Q.push(std::make_pair(this->getRaiz(), 0));

  os << "Nivel 0: ";
  //Recorremos la cola hasta que este vacia
  while (!Q.empty()) {
    //Guardamos el primer valor de la cola
    std::pair<NodoB<Key>*,int> p;
    p = Q.front();
    nodo = p.first;
    nivel = p.second;
    //Quitamos la pareja(nodo,nivel) de la Cola
    Q.pop();
    if(nivel > Nivel_actual) {
      Nivel_actual = nivel;
      os << "\nNivel " << Nivel_actual << ": ";
    }
    //Mostramos el valor del nodo
    if (nodo != nullptr) {
      os << "[" << nodo->getDato() << "]";
      Q.push(std::make_pair(nodo->getIzdo(),nivel + 1));
      Q.push(std::make_pair(nodo->getDcho(),nivel + 1));
    } else {
        os << "[.]";
    }
  }
  os << "\n";
}
