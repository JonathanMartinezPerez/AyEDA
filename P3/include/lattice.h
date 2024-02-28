#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "position.h"
#include "cell.h"
#include "factorycell.h"

class Lattice {
public:
    virtual ~Lattice() {}

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

    virtual void nextGeneration() override;
    virtual std::size_t Population();

    virtual std::ostream& display(std::ostream&) const override;
};
