#pragma once

#include <iostream>

#include "cell.h"
#include "position.h"

class Cell;

class FactoryCell {
    public:
        virtual Cell* createCell(const Position&, const State&) const = 0;
};

class FactoryCellAce100: public FactoryCell {
    public:
        Cell* createCell(const Position& ,const State&) const;
};


class FactoryCellAce30: public FactoryCell {
    public:
        Cell* createCell(const Position& ,const State&) const;
};

class FactoryCellLife23_3: public FactoryCell {
    public:
        Cell* createCell(const Position& ,const State&) const;
};

class FactoryCellLife51_346: public FactoryCell {
    public:
        Cell* createCell(const Position& ,const State&) const;
};
