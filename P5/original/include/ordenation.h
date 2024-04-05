// Autor: Jonathan Martínez Pérez
// Fichero: ordenation.h
#pragma once

#include <iostream>
#include <algorithm>

#include "sortmethod.h"
#include "sequence.h"
#include "library.h"

//Estas clases heredan de SortMethod y sobreescriben el método Sort llamando cada una a su función de ordenación correspondiente
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

template <class Key>
class Shell : public SortMethod<Key> {
    public:
        Shell(StaticSequence<Key>* sequence) : SortMethod<Key>(sequence) {}
        void Sort() const override {
            ShellSort(this->sequence_->getData(), this->sequence_->getSize());
        }
};

template <class Key>
class Radix : public SortMethod<Key> {
    public:
        Radix(StaticSequence<Key>* sequence) : SortMethod<Key>(sequence) {}
        void Sort() const override {
            RadixSort(this->sequence_->getData(), this->sequence_->getSize());
        }
};

template <class Key>
class Bin : public SortMethod<Key> {
    public:
        Bin(StaticSequence<Key>* sequence) : SortMethod<Key>(sequence) {}
        void Sort() const override {
            BinSort(this->sequence_->getData(), this->sequence_->getSize());
        }
};

template <class Key>
class Merge : public SortMethod<Key> {
    public:
        Merge(StaticSequence<Key>* sequence) : SortMethod<Key>(sequence) {}
        void Sort() const override {
            MergeSort(this->sequence_->getData(), 0, this->sequence_->getSize() - 1);
        }
};