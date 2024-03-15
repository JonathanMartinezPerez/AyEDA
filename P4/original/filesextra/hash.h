//hash.h
#pragma once

#include "sequence.h"
#include "function.h"
#include "exploration.h"

template <class Key, class Container = StaticSequence<Key>>
class HashTable : public Sequence<Key> {
  public:
    HashTable<Key,Container>::HashTable(unsigned sz, DispersionFunction<Key>& fd, ExplorationFunction<Key>& fe,unsigned bsz)
      : tableSize_(sz), fd_(fd), fe_(fe), blockSize_(bsz) {
        table_ = new Container[tableSize_];
      }
  private:
    size_t tableSize_; 
    Container* table_;
    DispersionFunction<Key>& fd_;
    ExplorationFunction<Key>& fe_;
    size_t blockSize_;
};