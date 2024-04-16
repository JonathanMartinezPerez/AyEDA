#pragma once

#include <iostream>

#include "AB.h"

template<typename Key>
class ABB : public AB<Key> {
public:
    ABB() : AB<Key>() {}

    bool insertar(const Key& k) override {
        if (AB<Key>::buscar(k)) {
            return false;
        }
        return AB<Key>::insertar(k);
    }
};
