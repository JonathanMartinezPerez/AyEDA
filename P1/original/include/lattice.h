//Practica 1 : Implementación de un autómata celular unidimensional
//Autor : <Jonathan Martínez Pérez>
//Correo : <alu0101254098@ull.edu.es>
//Archivo lattice.h

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "cell.h"

typedef int Position;

enum Frontier{
    COLD,
    HOT,
    PERIODIC,
};

class Cell;

class Lattice{

    public:
        Lattice(const int, const Frontier&);
        Lattice(const int, const Frontier&, const std::string&);
        ~Lattice();
 
        const Cell& getCell(const Position&) const;
        const std::vector<Cell*>& getCells() const;
        void nextGeneration();
        void ShowIterations();

        friend std::ostream& operator<<(std::ostream& , const Lattice&);


    private:
        std::vector<Cell*> cells_;
        int size_;
        Frontier border_;

};
std::ostream& operator<<(std::ostream&, const Lattice&);