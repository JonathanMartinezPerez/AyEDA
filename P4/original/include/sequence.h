//sequence.h
#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>

template<class Key>
class Sequence {
    public: 
        virtual bool search(const Key& k) const = 0;
        virtual bool insert(const Key& k) = 0;
        virtual ~Sequence() {}
};

template<class Key> 
class DynamicSequence: public Sequence<Key> {
    public:
        DynamicSequence() {}
        ~DynamicSequence() {}
        bool search(const Key& k) const;
        bool insert(const Key& k);
        std::vector<Key> getData() const {return data_;}
    private:
        std::vector<Key> data_;
};

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
        unsigned getSize() {return size_;}
        Key* getData() {return data_.data();}
    private:
        int size_;
        std::vector<Key> data_;
};

template<class Key>
bool DynamicSequence<Key>::search(const Key& k) const {
    for (long unsigned int i = 0; i < data_.size(); i++) {
        if (data_[i] == k) {
        return true;
        }
    }
    return false;
}

template <class Key>
bool DynamicSequence<Key>::insert(const Key& key) {
    if (!search(key)) {
        data_.push_back(key);
        return true;
    }
    return false;
}

template<class Key>
bool StaticSequence<Key>::isFull() const {
    for (int i = 0; i < size_; i++) {
        if (data_[i] == 0) {
            return false;
        }
    }
    return true;
}

template<class Key>
bool StaticSequence<Key>::search(const Key& k) const {
    for ( int i = 0; i < size_; i++ ) {
        if (data_[i] == k) {
        return true;
        }
    }
    return false;
}

template<class Key>
bool StaticSequence<Key>::insert(const Key& k) {
    if(isFull()) {
        std::cout << "The array is full" << std::endl;
        return false;
    }
    for (int i = 0; i < size_; i++) {
        if (data_[i] == 0) {
            data_[i] = k;
            return true;
        }
    }
    return false;
}
