//Autor: Jonathan Martínez Pérez
//Fichero: sequence.h
#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>


// Clase abstracta para implementar secuencias
template<class Key>
class Sequence {
    public: 
        virtual bool search(const Key& k) const = 0;
        virtual bool insert(const Key& k) = 0;
        virtual ~Sequence() {};
        virtual void build(unsigned sz) = 0;
        virtual bool isFull() const = 0;
        virtual unsigned getSize() const = 0;
        virtual const Key* getData() const = 0;
};

// Clase para implementar secuencias dinámicas
template<class Key> 
class DynamicSequence: public Sequence<Key> {
    public:
        DynamicSequence() {}
        ~DynamicSequence() {}
        bool search(const Key& k) const;
        bool insert(const Key& k);
        void build(unsigned sz) { sz++; }
        bool isFull() const {return false;}
        unsigned getSize() const override { return data_.size(); }
        const Key* getData() const override { return data_.data(); }
        
    private:
        std::vector<Key> data_;
};

// Clase para implementar secuencias estáticas
template<class Key> 
class StaticSequence: public Sequence<Key> {
    public:
        StaticSequence() {}
        ~StaticSequence() {
            data_.clear();
        }
        bool isFull() const;
        bool search(const Key& k) const;
        bool insert(const Key& k);
        void build(unsigned sz);
        unsigned getSize() const override { return size_; }
        const Key* getData() const override { return data_.data(); }
    private:
        int size_;
        std::vector<Key> data_;
};

// Implementación de las funcione search para las clases DynamicSequence
template<class Key>
bool DynamicSequence<Key>::search(const Key& k) const {
    for (unsigned i = 0; i < data_.size(); i++) {
        if (data_[i] == k) {
            return true;
        }
    }
    return false;
}

// Implementación de las funciones insert para las clases DynamicSequence
template <class Key>
bool DynamicSequence<Key>::insert(const Key& key) {
    if (search(key)) {
        std::cout << "El elemento "<< key <<" ya está en la secuencia" << std::endl;
        return false;
    }
    data_.push_back(key);
    return true;

}

template<class Key>
void StaticSequence<Key>::build(unsigned sz) {
    size_ = sz;
    data_ = std::vector<Key>(sz);
    //igualar todos los elementos a 0
    for (unsigned i = 0; i < sz; i++) {
        data_[i] = 0;
    }
}

// Implementación de las funciones isFull para StaticSequence
template<class Key>
bool StaticSequence<Key>::isFull() const {
    for (int i = 0; i < size_; i++) {
        if (data_[i] == Key(0)) {
            return false;
        }
    }
    return true;
}

// Implementación de las funciones search para StaticSequence
template<class Key>
bool StaticSequence<Key>::search(const Key& k) const {
    for ( int i = 0; i < size_; i++ ) {
        if (data_[i] == k) {
        return true;
        }
    }
    return false;
}

// Implementación de las funciones insert para StaticSequence
template<class Key>
bool StaticSequence<Key>::insert(const Key& k) {
    if(isFull()) {
        return false;
    }
    if (search(k)) {
        std::cout << "El elemento "<< k <<" ya está en la secuencia" << std::endl;
        return false;
    }
        for (int i = 0; i < size_; i++) {
            if (data_[i] == Key(0)) {
                data_[i] = k;
                return true;
            }
        }
    
    return false;
}
