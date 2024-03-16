//sequence.h
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
        unsigned getSize() const override { return data_.size(); }
        const Key* getData() const override { return data_.data(); }
        
    private:
        std::vector<Key> data_;
};

// Clase para implementar secuencias estáticas
template<class Key> 
class StaticSequence: public Sequence<Key> {
    public:
        StaticSequence(unsigned size) {
            size_ = size;
            data_ = std::vector<Key>(size);
        }
        ~StaticSequence() {
            data_.clear();
        }
        bool isFull() const;
        bool search(const Key& k) const;
        bool insert(const Key& k);
        unsigned getSize() const override { return size_; }
        const Key* getData() const override { return data_.data(); }
    private:
        int size_;
        std::vector<Key> data_;
};

// Implementación de las funcione search para las clases DynamicSequence
template<class Key>
bool DynamicSequence<Key>::search(const Key& k) const {
    for (long unsigned int i = 0; i < data_.size(); i++) {
        if (data_[i] == k) {
        return true;
        }
    }
    return false;
}

// Implementación de las funciones insert para las clases DynamicSequence
template <class Key>
bool DynamicSequence<Key>::insert(const Key& key) {
    if (!search(key)) {
        data_.push_back(key);
        return true;
    }
    return false;
}

// Implementación de las funciones isFull para StaticSequence
template<class Key>
bool StaticSequence<Key>::isFull() const {
    for (int i = 0; i < size_; i++) {
        if (data_[i] == Key()) {
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
        std::cout << "El array esta lleno" << std::endl;
        return false;
    }
    for (int i = 0; i < size_; i++) {
        if (data_[i] == Key()) {
            data_[i] = k;
            return true;
        }
    }
    return false;
}
