//position.h
#pragma once

#include <iostream>
#include <cstdarg>
#include <stdexcept>
#include <stdarg.h>

typedef int Coor_t;

class Position {
    public:
        virtual ~Position() {}

        virtual Coor_t operator[](unsigned int) const = 0;
};

template <int Dim, class Coordinate_t=int>
class PositionDim: public Position {
    public:
        PositionDim(int sz, ...);

        virtual Coor_t operator[](unsigned int) const override;

    private:
        Coor_t Coordinates[Dim];
};

template <int Dim, class Coordinate_t>
PositionDim<Dim, Coordinate_t>::PositionDim(int sz, ...) {
    va_list args;
    va_start(args, sz);
    for (int i = 0; i < Dim; i++) {
        Coordinates[i] = va_arg(args, Coordinate_t);
    }
    va_end(args);
}

template <int Dim, class Coordinate_t>
Coor_t PositionDim<Dim, Coordinate_t>::operator[](unsigned int index) const {
    if (index < Dim) {
        return Coordinates[index];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

