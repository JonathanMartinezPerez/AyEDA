#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>

template<class Key>
class Sequence {
    public: 
        virtual bool search(const Key& k) const = 0;
        virtual bool insert(const Key& k) = 0;
};

template<class Key> 
class DynamicSequence: public Sequence<Key> {
    public:
        DynamicSequence() {
            data_ = std::vector<Key>();
        }
        ~DynamicSequence() {
            data_.clear();
        }
        
        bool search(const Key& k) const;
        bool insert(const Key& k);
        void print(std::ostream& os) const{
            for (long unsigned int i = 0; i < data_.size(); i++) {
                os << data_[i] << " ";
            }
            os << std::endl;
        }
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
        void print(std::ostream& os) const{
            for (int i = 0; i < size_; i++) {
                os << data_[i] << " ";
            }
            os << std::endl;
        }
        unsigned getSize() {return size_;}
        Key* getData() {return data_;}
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

template<class Key>
bool DynamicSequence<Key>::insert(const Key& k) {
    data_.push_back(k);
    return true;
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
