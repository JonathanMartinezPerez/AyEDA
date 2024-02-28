#include "lattice.h"

Lattice1D::Lattice1D(int size, const FactoryCell& factory) {
    for (int i = 0; i < size; i++) {
        cells.push_back(factory.createCell(Position1D(i), State::DEAD));
    }
}

Lattice1D::~Lattice1D() {
    for (Cell* cell : cells) {
        delete cell;
    }
}

void Lattice1D::nextGeneration() {
    for (Cell* cell : cells) {
        cell->nextState(*this);
    }
    for (Cell* cell : cells) {
        cell->updateState();
    }
}

std::size_t Lattice1D::Population() const {
    std::size_t population = 0;
    for (Cell* cell : cells) {
        if (cell->getState() == State::ALIVE) {
            population++;
        }
    }
    return population;
}

std::ostream& Lattice1D::display(std::ostream& os) const {
    for (Cell* cell : cells) {
        os << *cell;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
    return lattice.display(os);
}

Lattice2D::Lattice2D(int rows, int cols, const FactoryCell& factory) {
    for (int i = 0; i < rows; i++) {
        std::vector<Cell*> row;
        for (int j = 0; j < cols; j++) {
            row.push_back(factory.createCell(Position2D(i, j), State::DEAD));
        }
        cells.push_back(row);
    }
}

Lattice2D::~Lattice2D() {
    for (std::vector<Cell*>& row : cells) {
        for (Cell* cell : row) {
            delete cell;
        }
    }
}

void Lattice2D::nextGeneration() {
    for (std::vector<Cell*>& row : cells) {
        for (Cell* cell : row) {
            cell->nextState(*this);
        }
    }
    for (std::vector<Cell*>& row : cells) {
        for (Cell* cell : row) {
            cell->updateState();
        }
    }
}

std::size_t Lattice2D::Population() {
    std::size_t population = 0;
    for (std::vector<Cell*>& row : cells) {
        for (Cell* cell : row) {
            if (cell->getState() == State::ALIVE) {
                population++;
            }
        }
    }
    return population;
}

std::ostream& Lattice2D::display(std::ostream& os) const {
    for (std::vector<Cell*> row : cells) {
        for (Cell* cell : row) {
            os << *cell;
        }
        os << std::endl;
    }
    return os;
}



