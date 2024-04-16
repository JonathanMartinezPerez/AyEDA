#pragma once

#include <iostream>

#include "AB.h"

template<typename Key>
class ABE : public AB<Key> {
public:
    ABE() : AB<Key>() {}

    bool insertar(const Key& k) override {
        if (AB<Key>::insertar(k)) {
            return true;
        }
        return false;
    }
};

