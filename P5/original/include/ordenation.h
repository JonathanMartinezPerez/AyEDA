#pragma once

#include <iostream>
#include <algorithm>

#include "sortmethod.h"
#include "sequence.h"
#include "library.h"

template <class Key>
class Selection : public SortMethod<Key> {
    public:
        Selection(StaticSequence<Key>* sequence) : SortMethod<Key>(sequence) {}
        void Sort() const override {
            SelectionSort(this->sequence_->getData(), this->sequence_->getSize());
        }
};

template <class Key>
class Quick : public SortMethod<Key> {
    public:
        Quick(StaticSequence<Key>* sequence) : SortMethod<Key>(sequence) {}
        void Sort() const override {
            QuickSort(this->sequence_->getData(), 0, this->sequence_->getSize() - 1);
        }
};

template <class Key>
class Heap : public SortMethod<Key> {
    public:
        Heap(StaticSequence<Key>* sequence) : SortMethod<Key>(sequence) {}
        void Sort() const override {
            HeapSort(this->sequence_->getData(), this->sequence_->getSize());
        }
};