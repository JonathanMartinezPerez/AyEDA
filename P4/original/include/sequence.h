#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <list>

// Clase sequence
template <class Key>
class Sequence {
    public:
        virtual bool search(const Key& key) const = 0;
        virtual bool insert(const Key& key) = 0;
        virtual ~Sequence() {}
};

// Clase dinamic sequence que hereda de sequence
template <class Key>
class DynamicSequence : public Sequence<Key> {
    public:
        DynamicSequence() {}
        bool search(const Key& key) const override;
        bool insert(const Key& key) override;
    private:
        std::vector<Key> elements_; // Lista para almacenar los elementos en caso de colisión
};

// Implementación de los métodos de la clase DynamicSequence
template<class Key>
bool DynamicSequence<Key>::search (const Key& key) const {
    for (const auto& k : elements_) {
        if (k == key) {
            return true;
        }
    }
    return false;
}

// Implementación de los métodos de la clase DynamicSequence
template <class Key>
bool DynamicSequence<Key>::insert(const Key& key) {
    if (!search(key)) {
        elements_.push_back(key);
        return true;
    }
    return false;
}

// Clase static sequence que hereda de sequence
template <class Key>
class StaticSequence : public Sequence<Key> {
    public:
        StaticSequence(size_t tSize, DispersionFunction<Key>& fd, ExplorationFunction<Key>& fe, size_t bSize) 
        : tableSize_(tSize), fd_(fd), fe_(fe), blockSize_(bSize) {
            table_ = new Sequence<Key>*[tableSize_];
            for (size_t i = 0; i < tableSize_; i++) {
            table_[i] = new Container[blockSize_];
            }
        }
        bool search(const Key& key) const override;
        bool insert(const Key& key) override;
        bool isFull() const;
    private:
        size_t tableSize_;
        Sequence<Key>** table_;
        DispersionFunction<Key>& fd_;
        ExplorationFunction<Key>& fe_;
        size_t blockSize_;
};
