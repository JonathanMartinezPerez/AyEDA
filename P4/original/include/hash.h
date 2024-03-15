//hash.h
#pragma once
#include "sequence.h"
#include "function.h"

template <class Key, class Container = StaticSequence<Key>>
class HashTable : public Sequence <Key> {
  public:
    HashTable (unsigned int tsz, DispersionFunction<Key>& fd, ExplorationFunction<Key>& fe, unsigned bsz)
      : tableSize_(tsz), fd_(fd), fe_(fe), blockSize_(bsz) {
        hashTable_ = new Container*[tableSize_];
        for (unsigned int i = 0; i < tableSize_; i++) {
          hashTable_[i] = new Container{blockSize_};
        }
      }
    bool search(const Key& key) const;
    bool insert(const Key& key);
    void display() const;
  private:
    unsigned int tableSize_;
    DispersionFunction<Key>& fd_;
    ExplorationFunction<Key>& fe_;  
    unsigned int blockSize_;
    Container** hashTable_;
};

template <class Key, class Container>
bool HashTable<Key, Container>::insert(const Key& key) {
  int position{0};
  for (unsigned int i = 0; i < tableSize_; i++) {
    position += (fe_(key, i) + fd_(key));
    position = position % tableSize_;
    if (hashTable_[position]->insert(key) == true) {
      return true;
    }
  }
  return false;
}

template <class Key, class Container>
bool HashTable<Key, Container>::search(const Key& key) const {
  int position{0};
  for (unsigned int i = 0; i < tableSize_; i++) {
    position += (fe_(key, i) + fd_(key));
    position = position % tableSize_;
    if (hashTable_[position]->search(key) == true) {
      return true;
    }
  }
  return false;
}

template <class Key, class Container>
void HashTable<Key, Container>::display() const {
  for (unsigned int i = 0; i < tableSize_; i++) {
    std::cout << "Posicion " << i << ": ";
    for (unsigned int j = 0; j < hashTable_[i]->getSize(); j++) {
      std::cout << hashTable_[i]->getData()[j] << " ";
    }
    std::cout << std::endl;
  }
}

template <class Key>
class HashTable <Key, DynamicSequence<Key>> {
  public:
    HashTable (unsigned tsz, DispersionFunction<Key>& fd) : tableSize_(tsz), fd_(fd) { 
      hashTable_ = new DynamicSequence<Key>*[tableSize_];
    }
    bool search(const Key& key) const;
    bool insert(const Key& key);
    void display() const;
  private:
    DispersionFunction<Key> fd_;
    unsigned int tableSize_;
    Sequence<Key>* hashTable_;
};


template <class Key>
bool HashTable<Key, DynamicSequence<Key>>::insert(const Key& key) {
  unsigned int position{0};
  position = fd_(key);
  position = position % tableSize_;
  if (hashTable_[position]->insert(key) == true) {
    return true;
  }
  return false;
}


template <class Key>
bool HashTable<Key, DynamicSequence<Key>>::search(const Key& key) const {
  unsigned int position{0};
  position = fd_(key);
  position = position % tableSize_;
  if (hashTable_[position]->search(key) == true) {
    return true;
  }
  return false;
}

template <class Key>
void HashTable<Key, DynamicSequence<Key>>::display() const {
  for (unsigned int i = 0; i < tableSize_; i++) {
    std::cout << "Posicion " << i << ": ";
    for (unsigned int j = 0; j < hashTable_[i]->getSize(); j++) {
      std::cout << hashTable_[i]->getData()[j] << " ";
    }
    std::cout << std::endl;
  }
}