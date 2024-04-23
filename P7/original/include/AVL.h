#pragma once

#include "AB.h"
#include "ABB.h"
#include "nodoAVL.h"

template<typename Key>
class AVL : public ABB<Key>{
    public:
        AVL() : ABB<Key>(){
            raiz = nullptr;
        }

        bool insertar(const Key& k) override;
        void insertarBalanceado(NodoAVL<Key>* &nodo, NodoAVL<Key>* &nuevo, bool& crece);
        void insertarReBalanceaIzquierda(NodoAVL<Key>* &nodo, bool& crece);
        void insertarReBalanceaDerecha  (NodoAVL<Key>* &nodo, bool& crece);

        bool equilibrio(void);

        void rotacionII(NodoAVL<Key>* &nodo);
        void rotacionID(NodoAVL<Key>* &nodo);
        void rotacionDI(NodoAVL<Key>* &nodo);
        void rotacionDD(NodoAVL<Key>* &nodo);

        NodoAVL<Key>*& getRaiz() { return raiz; }

    private:
        bool insertarRamaAVL(NodoAVL<Key>* nodo, const Key& k);
        bool equilibrioRama(NodoAVL<Key>* nodo);
        NodoAVL<Key>* raiz;
};

template <typename Key>
void AVL<Key>::insertarReBalanceaIzquierda(NodoAVL<Key>* &nodo, bool& crece) {
  switch (nodo->getBal()) {
    case -1:
      nodo->setBal(0);
      crece = false;
      break;
    case 0:
      nodo->setBal(1);
      break;
    case 1:
      NodoAVL<Key>* nodo1 = nodo->getIzdo();
      if (nodo1->getBal() == 1) {
        rotacionII(nodo);
      } else {
        rotacionID(nodo);
      }
      crece = false;
      break;
  }
}

template <typename Key>
void AVL<Key>::insertarReBalanceaDerecha(NodoAVL<Key>* &nodo, bool& crece) {
  switch (nodo->getBal()) {
    case 1:
      nodo->setBal(0);
      crece = false;
      break;
    case 0:
      nodo->setBal(-1);
      break;
    case -1:
      NodoAVL<Key>* nodo1 = nodo->getDcho();
      if (nodo1->getBal() == -1) {
        rotacionDD(nodo);
      } else {
        rotacionDI(nodo);
      }
      crece = false;
      break;
  }
}

template <typename Key>
bool AVL<Key>::insertar(const Key& k) {
  if (this->buscar(k))
   return false;
  else {
    NodoAVL<Key>* nuevo = new NodoAVL<Key>(k);
    nuevo->setBal(0);
    bool crece = false;
    insertarBalanceado(this->getRaiz(), nuevo, crece);
    this->mostrarPorNiveles(std::cout);
    return true;
  }
}

template <typename Key>
void AVL<Key>::insertarBalanceado(NodoAVL<Key>* &nodo, NodoAVL<Key>* &nuevo, bool& crece) {
  if (nodo == nullptr) {
    nodo = nuevo;
    crece = true;
  } else if (nuevo->getDato() < nodo->getDato()) {
    insertarBalanceado(nodo->getIzdo() , nuevo, crece);
    if (crece)
      insertarReBalanceaIzquierda(nodo, crece);
  } else {
    insertarBalanceado(nodo->getDcho() , nuevo, crece);
    if (crece)
      insertarReBalanceaDerecha(nodo, crece);
  }
}

template<typename Key>
bool AVL<Key>::equilibrio(void) {
    return equilibrioRama(this->raiz);
}

template<typename Key>
bool AVL<Key>::equilibrioRama(NodoAVL<Key>* nodo) {
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

template <typename Key>
void AVL<Key>::rotacionII(NodoAVL<Key>* &nodo) {
    /*
    if (AB<Key>::getTraceMode()) {
        std::cout << *this << std::endl;
        std::cout << "Rotacion II en [" << nodo->getDato()  << "]:" << std::endl;
    }
    */
    NodoAVL<Key>* nodo1 = nodo->getIzdo();
    nodo->getIzdo() = nodo1->getDcho();
    nodo1->getDcho() = nodo;

    if (nodo1->getBal() == 1) {
        nodo->getBal() = 0;
        nodo1->getBal() = 0;
    } else {
        nodo->getBal() = 1;
        nodo1->getBal() = -1;
    }
    nodo = nodo1;
}

template <typename Key>
void AVL<Key>::rotacionDD(NodoAVL<Key>* &nodo) {
    /*
    if (AB<Key>::getTraceMode()) {
        std::cout << *this << std::endl;
        std::cout << "Rotacion DD en [" << nodo->getDato()  << "]:" << std::endl;
    }
    */
    NodoAVL<Key>* nodo1 = nodo->getDcho();
    nodo->getDcho() = nodo1->getIzdo();
    nodo1->getIzdo() = nodo;

    if (nodo1->getBal() == -1) {
        nodo->getBal() = 0;
        nodo1->getBal() = 0;
    } else {
        nodo->getBal() = -1;
        nodo1->getBal() = 1;
    }
    nodo = nodo1;
}

template <typename Key>
void AVL<Key>::rotacionID(NodoAVL<Key>* &nodo) {
    /*
    if (AB<Key>::getTraceMode()) {
        std::cout << *this << std::endl;
        std::cout << "Rotacion ID en [" << nodo->getDato()  << "]:" << std::endl;
    }
    */
    NodoAVL<Key>* nodo1 = nodo->getIzdo();
    NodoAVL<Key>* nodo2 = nodo1->getDcho();
    nodo->getIzdo() = nodo2->getDcho();
    nodo2->getDcho() = nodo;
    nodo1->getDcho() = nodo2->getIzdo();
    nodo2->getIzdo() = nodo1;

    if (nodo2->getBal() == -1) {
        nodo1->getBal() = 1;
    } else {
        nodo1->getBal() = 0;
    }
    if (nodo2->getBal() == 1) {
        nodo->getBal() = -1;
    } else {
        nodo->getBal() = 0;
    }
    nodo2->getBal() = 0;
    nodo = nodo2;
}

template <typename Key>
void AVL<Key>::rotacionDI(NodoAVL<Key>* &nodo) {
    /*
    if (AB<Key>::getTraceMode()) {
        std::cout << *this << std::endl;
        std::cout << "Rotacion DI en [" << nodo->getDato()  << "]:" << std::endl;
    }
    */  
    NodoAVL<Key>* nodo1 = nodo->getDcho();
    NodoAVL<Key>* nodo2 = nodo1->getIzdo();
    nodo->getDcho() = nodo2->getIzdo();
    nodo2->getIzdo() = nodo;
    nodo1->getIzdo() = nodo2->getDcho();
    nodo2->getDcho() = nodo1;

    if (nodo2->getBal() == 1) {
        nodo1->getBal() = -1;
    } else {
        nodo1->getBal() = 0;
    }
    if (nodo2->getBal() == -1) {
        nodo->getBal() = 1;
    } else {
        nodo->getBal() = 0;
    }
    nodo2->getBal() = 0;
    nodo = nodo2;
}