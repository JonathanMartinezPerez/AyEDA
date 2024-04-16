#pragma once

#include <iostream>
#include "nodoB.h"

template<typename Key>
class AB {
public:
    AB() : raiz(nullptr) {}

    // Destructor
    ~AB() {
        limpiar(raiz);
    }

    virtual bool insertar(const Key& k) {
        return insertarRecursivo(raiz, k);
    }

    bool buscar(const Key& k) const {
        return buscarRecursivo(raiz, k);
    }

    void inorden() const {
        inordenRecursivo(raiz);
    }

    friend std::ostream& operator<<(std::ostream& os, const AB<Key>& arbol) {
        arbol.mostrarPorNiveles(os, arbol.raiz, 0);
        return os;
    }

protected:
    NodoB<Key>* raiz;

    void limpiar(NodoB<Key>* nodo) {
        if (nodo != nullptr) {
            limpiar(nodo->izdo);
            limpiar(nodo->dcho);
            delete nodo;
        }
    }

    bool insertarRecursivo(NodoB<Key>*& nodo, const Key& k) {
        if (nodo == nullptr) {
            nodo = new NodoB<Key>(k);
            return true;
        }
        if (k < nodo->dato) {
            return insertarRecursivo(nodo->izdo, k);
        } else if (k > nodo->dato) {
            return insertarRecursivo(nodo->dcho, k);
        }
        return false; // El valor ya existe en el árbol
    }

    bool buscarRecursivo(NodoB<Key>* nodo, const Key& k) const {
        if (nodo == nullptr) {
            return false;
        }
        if (k == nodo->dato) {
            return true;
        }
        if (k < nodo->dato) {
            return buscarRecursivo(nodo->izdo, k);
        } else {
            return buscarRecursivo(nodo->dcho, k);
        }
    }

    void inordenRecursivo(NodoB<Key>* nodo) const {
        if (nodo != nullptr) {
            inordenRecursivo(nodo->izdo);
            std::cout << nodo->dato << " ";
            inordenRecursivo(nodo->dcho);
        }
    }

    void mostrarPorNiveles(std::ostream& os, NodoB<Key>* nodo, int nivel) const {
        if (nodo == nullptr) {
            os << "[.]";
            return;
        }

        // Mostrar el nodo actual
        os << "[" << nodo->dato << "]";

        // Si tiene hijos, mostrarlos en el siguiente nivel
        if (nodo->izdo != nullptr || nodo->dcho != nullptr) {
            os << std::endl;

            // Mostrar el subárbol izquierdo
            for (int i = 0; i < nivel + 1; ++i) {
                os << "    ";
            }
            mostrarPorNiveles(os, nodo->izdo, nivel + 1);

            // Mostrar el subárbol derecho
            if (nodo->dcho != nullptr) {
                os << std::endl;
                for (int i = 0; i < nivel + 1; ++i) {
                    os << "    ";
                }
                mostrarPorNiveles(os, nodo->dcho, nivel + 1);
            }
        }
    }
};
