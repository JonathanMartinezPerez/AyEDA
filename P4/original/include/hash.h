#pragma once
#include "sequence.h"
#include "function.h"

template<class Key, class Container=StaticSequence<Key>>
class HashTable {
public:
    HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration, unsigned blocksize);
    ~HashTable();
    void display(std::ostream& os) const;
private:
    unsigned tablesize_;
    DispersionFunction<Key>& dispersion_;
    ExplorationFunction<Key>& exploration_;
    unsigned blockSize_;
    Container** container_;
};

// Implementación del constructor de HashTable
template<class Key, class Container>
HashTable<Key, Container>::HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration, unsigned blocksize)
    : tablesize_(table_size), dispersion_(dispersion), exploration_(exploration), blockSize_(blocksize) {
    container_ = new Container*[table_size];
    for (unsigned i = 0; i < table_size; ++i) {
        container_[i] = new Container[blocksize];
    }
}

// Implementación del destructor de HashTable
template<class Key, class Container>
HashTable<Key, Container>::~HashTable() {
    for (unsigned i = 0; i < tablesize_; ++i) {
        delete[] container_[i];
    }
    delete[] container_;
}

// Implementación del método display
template<class Key, class Container>
void HashTable<Key, Container>::display(std::ostream& os) const {
    for (unsigned i = 0; i < tablesize_; ++i) {
        os << "Celda " << i << ": ";
        container_[i]->print(os);
    }
}
