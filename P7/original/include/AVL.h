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
    
    virtual bool buscar(const Key& k) const override;

    NodoAVL<Key>*& getRaiz() { return raiz; }
    NodoAVL<Key>* getRaiz() const { return raiz; }

private:
    bool insertarRamaAVL(NodoAVL<Key>* nodo, const Key& k);
    bool equilibrioRama(NodoAVL<Key>* nodo);
    NodoAVL<Key>* raiz;
    
    bool buscarRama(NodoAVL<Key>* nodo, const Key& k) const;
    void mostrarPorNiveles2(std::ostream& os) const;
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
    if (this->buscar(k)){
        std::cout << "El dato: " << k << " ya existe en el arbol" << std::endl;
        return false;
    } else {
        NodoAVL<Key>* nuevo = new NodoAVL<Key>(k);
        nuevo->setBal(0);
        bool crece = false;
        insertarBalanceado(this->getRaiz(), nuevo, crece);
        mostrarPorNiveles2(std::cout);
        return true;
    }
}

template <typename Key>
void AVL<Key>::insertarBalanceado(NodoAVL<Key>* &nodo, NodoAVL<Key>* &nuevo, bool& crece) {
    if (nodo == nullptr) {
        nodo = nuevo;
        crece = true;
    } else if (nuevo->getDato() < nodo->getDato()) {
        insertarBalanceado(nodo->getIzdo(), nuevo, crece);
        if (crece)
            insertarReBalanceaIzquierda(nodo, crece);
    } else {
        insertarBalanceado(nodo->getDcho(), nuevo, crece);
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

    int eq = this->tamRama(nodo->getIzdo()) - this->tamRama(nodo->getDcho());

    switch (eq){
        case -1:
        case 0:
        case 1:
            return equilibrioRama(nodo->getIzdo()) && equilibrioRama(nodo->getDcho());
        default:
            return false;
    }
}

template <typename Key>
void AVL<Key>::rotacionII(NodoAVL<Key>* &nodo) {
    NodoAVL<Key>* nodo1 = nodo->getIzdo();
    nodo->setIzdo(nodo1->getDcho());
    nodo1->setDcho(nodo);

    if (nodo1->getBal() == 1) {
        nodo->setBal(0);
        nodo1->setBal(0);
    } else {
        nodo->setBal(1);
        nodo1->setBal(-1);
    }
    nodo = nodo1;
}

template <typename Key>
void AVL<Key>::rotacionDD(NodoAVL<Key>* &nodo) {
    NodoAVL<Key>* nodo1 = nodo->getDcho();
    nodo->setDcho(nodo1->getIzdo());
    nodo1->setIzdo(nodo);

    if (nodo1->getBal() == -1) {
        nodo->setBal(0);
        nodo1->setBal(0);
    } else {
        nodo->setBal(-1);
        nodo1->setBal(1);
    }
    nodo = nodo1;
}

template <typename Key>
void AVL<Key>::rotacionID(NodoAVL<Key>* &nodo) {
    NodoAVL<Key>* nodo1 = nodo->getIzdo();
    NodoAVL<Key>* nodo2 = nodo1->getDcho();
    nodo->setIzdo(nodo2->getDcho());
    nodo2->setDcho(nodo);
    nodo1->setDcho(nodo2->getIzdo());
    nodo2->setIzdo(nodo1);

    if (nodo2->getBal() == -1) {
        nodo1->setBal(1);
    } else {
        nodo1->setBal(0);
    }
    if (nodo2->getBal() == 1) {
        nodo->setBal(-1);
    } else {
        nodo->setBal(0);
    }
    nodo2->setBal(0);
    nodo = nodo2;
}

template <typename Key>
void AVL<Key>::rotacionDI(NodoAVL<Key>* &nodo) {
    NodoAVL<Key>* nodo1 = nodo->getDcho();
    NodoAVL<Key>* nodo2 = nodo1->getIzdo();
    nodo->setDcho(nodo2->getIzdo());
    nodo2->setIzdo(nodo);
    nodo1->setIzdo(nodo2->getDcho());
    nodo2->setDcho(nodo1);

    if (nodo2->getBal() == 1) {
        nodo1->setBal(-1);
    } else {
        nodo1->setBal(0);
    }
    if (nodo2->getBal() == -1) {
        nodo->setBal(1);
    } else {
        nodo->setBal(0);
    }
    nodo2->setBal(0);
    nodo = nodo2;
}

template<typename Key>
bool AVL<Key>::buscar(const Key& k) const {
    return buscarRama(this->raiz, k);
}

template<typename Key>
bool AVL<Key>::buscarRama(NodoAVL<Key>* nodo, const Key& k) const {
    if (nodo == nullptr) {
        return false;
    }
    if (k == nodo->getDato()) {
        return true;
    }
    if (k < nodo->getDato()) {
        return buscarRama(nodo->getIzdo(), k);
    }
    return buscarRama(nodo->getDcho(), k);
}

template<typename Key>
void AVL<Key>::mostrarPorNiveles2(std::ostream& os) const {
  std::queue<std::pair<NodoAVL<Key>*,int>> Q;
  NodoAVL<Key> *nodo;
  int nivel, Nivel_actual = 0;
  Q.push(std::make_pair(getRaiz(), 0)); 

  os << "Nivel 0: ";
  //Recorremos la cola hasta que este vacia
  while (!Q.empty()) {
    //Guardamos el primer valor de la cola
    std::pair<NodoAVL<Key>*,int> p;
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