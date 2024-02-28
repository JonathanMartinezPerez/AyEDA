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

template <int Dim=2, class Coordinate_t=int>
class PositionDim: public Position {
    public:
        PositionDim(int sz, ...);

        virtual Coor_t operator[](unsigned int) const override;

    private:
        Coor_t Coordinates[Dim];
};

