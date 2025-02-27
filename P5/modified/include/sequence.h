//Autor: Jonathan Martínez Pérez
//Fichero: sequence.h
#pragma once

#include <iostream>
#include <vector>

typedef int Position;

// Clase abstracta para implementar secuencias
template<class Key>
class Sequence {
    public: 
        virtual ~Sequence() {};
        virtual bool insert(const Key& k) = 0;
        virtual bool isFull() const = 0;
        virtual Key operator[](const Position&) const = 0;
        virtual int getSize() const = 0;
        virtual const std::vector<Key>& getData() const = 0;
        virtual std::vector<Key>& getData() = 0;
};

// Clase para implementar secuencias estáticas
template<class Key> 
class StaticSequence: public Sequence<Key> {
    public:
        StaticSequence(int size){    
            size_= size;
            data_.resize(size_);
            for (int i = 0; i < size_; i++) {
                data_[i] = Key(0);
            }
        };
        ~StaticSequence() = default;
        bool isFull() const;
        bool insert(const Key& k);
        Key operator[](const Position&) const override;

        std::vector<Key>& getData() override { return data_; }
        const std::vector<Key>& getData() const override { return data_; }

        int getSize() const override { return size_; }
    private:
        int size_;
        std::vector<Key> data_;
};

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

// Implementación de las funciones insert para StaticSequence
template<class Key>
bool StaticSequence<Key>::insert(const Key& k) {
    if(isFull()) {
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

// Implementación de las funciones operator[] para StaticSequence
template<class Key>
Key StaticSequence<Key>::operator[](const Position& p) const {
    if (p < 0 || p > size_) {
        std::cout << "Posición no válida" << std::endl;
        return Key(0);
    }
    return data_[p];
}