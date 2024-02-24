//Practica 2 : Implementación de un autómata celular bidimensional
//Autor : <Jonathan Martínez Pérez>
//Correo : <alu0101254098@ull.edu.es>
//Archivo lattice.h

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <limits>


#include "cell.h"

typedef std::pair<int, int> Position;

enum Frontier{
    COLD,
    HOT,
    PERIODIC,
    REFLECTIVE,
    NOFRONTIER,
};

class Cell;

class Lattice{

    public:
        Lattice(const int, const int, const Frontier&);
        Lattice(const char*, const Frontier&);
        ~Lattice();

        const Cell& getCell(const Position&) const;
        const std::vector<std::vector<Cell*>>& getCells() const;

        int getWidth() const;
        int getHeight() const;

        void nextGeneration();
        void ShowIterations();
        std::size_t Population() const;

        friend std::ostream& operator<<(std::ostream& , const Lattice&);

    private:
        std::vector<std::vector<Cell*>> cells_;
        int width_;
        int height_;
        Frontier border_;
        Cell& operator[](const Position&) const;

};
std::ostream& operator<<(std::ostream&, const Lattice&);