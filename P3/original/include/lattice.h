//lattice.h
#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "factorycell.h"

class Cell;

class Lattice {
public:
    virtual ~Lattice() {}

    virtual Cell& operator[](const Position&) const = 0;

    virtual void nextGeneration() = 0;
    virtual std::size_t Population() const = 0;

    virtual std::ostream& display(std::ostream&) const = 0;
    friend std::ostream& operator<<(std::ostream&, const Lattice&);
};

class Lattice1D : public Lattice {
private:
    std::vector<Cell*> cells;

public:
    Lattice1D(int, const FactoryCell&);
    virtual ~Lattice1D();

    virtual Cell& operator[](const Position&) const override;

    virtual void nextGeneration() override;
    virtual std::size_t Population() const override;

    virtual std::ostream& display(std::ostream&) const override;
};

class Lattice2D : public Lattice {
private:
    std::vector<std::vector<Cell*>> cells;

public:
    Lattice2D(int, int, const FactoryCell&);
    virtual ~Lattice2D();

    virtual Cell& operator[](const Position&) const override;

    virtual void nextGeneration() override;
    virtual std::size_t Population();

    virtual std::ostream& display(std::ostream&) const override;
};

class Lattice1Dopen : public Lattice1D {};

class Lattice1Dperiodic : public Lattice1D {};

class Lattice2Dopen : public Lattice2D {};

class Lattice2Dperiodic : public Lattice2D {};

class Lattice2Dreflective : public Lattice2D {};

class Lattice2Dnoborders : public Lattice2D {};