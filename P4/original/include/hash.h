//hash.h
#pragma once
#include "sequence.h"
#include "function.h"

// Clase para implementar la tabla hash
template <class Key, class Container = StaticSequence<Key>>
class HashTable {
  public:
    HashTable (unsigned int tsz, DispersionFunction<Key>& fd, ExplorationFunction<Key>& fe, unsigned bsz)
      : tableSize_(tsz), fd_(fd), fe_(fe), blockSize_(bsz) {
        hashTable_ = new Container[tableSize_];
        for (unsigned int i = 0; i < tableSize_; i++) {
          hashTable_[i].build(bsz);
        }
      }
    ~HashTable() {delete[] hashTable_;}
    bool search(const Key& key) const;
    bool insert(const Key& key);
    void display() const;
  private:
    unsigned int tableSize_;
    DispersionFunction<Key>& fd_;
    ExplorationFunction<Key>& fe_;  
    unsigned int blockSize_;
    Container* hashTable_;
};

// Implementación de las funcion insertar para la clase HashTable
template <class Key, class Container>
bool HashTable<Key, Container>::insert(const Key& key) {
  unsigned iteration = 0;
  if (this->search(key)) {
    std::cout << "El elemento "<< key << " ya existe en la tabla" << std::endl;
    return false;
  } else {
    do {
      if (!hashTable_[fd_(key)].isFull()) {
        hashTable_[fd_(key)].insert(key);
        return true;
      } else {
        unsigned position = (fd_(key) + fe_(key, iteration));
        position = position % tableSize_;
        if (hashTable_[position].insert(key)) {
          return true;
        }
      }
      iteration++;
    } while (iteration < tableSize_);
  }
  return false;
}

// Implementación de las funcion buscar para la clase HashTable
template <class Key, class Container>
bool HashTable<Key, Container>::search(const Key& key) const {

  unsigned iteration = 0;
  do {
    if (hashTable_[fd_(key)].search(key)) {
      return true;
    } else  {
      unsigned position = (fd_(key) + fe_(key, iteration));
      position = position % tableSize_;
      if (hashTable_[position].search(key)) {
        return true;
      }
    }
    iteration++;
  } while (iteration < tableSize_);
  return false;
}

// Implementación de la funcion display para la clase HashTable
template <class Key, class Container>
void HashTable<Key, Container>::display() const {
  for (unsigned int i = 0; i < tableSize_; i++) {
    std::cout << "Posicion " << i << ": ";
    for (unsigned int j = 0; j < hashTable_[i].getSize(); j++) {
      std::cout << hashTable_[i].getData()[j] << " ";
    }
    std::cout << std::endl;
  }
}
