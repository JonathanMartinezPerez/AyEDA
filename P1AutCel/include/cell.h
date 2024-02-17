//Practica 1 : Implementación de un autómata celular unidimensional
//Autor : <Jonathan Martínez Pérez>
//Correo : <alu0101254098@ull.edu.es>
//Archivo cell.h

#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "lattice.h"

typedef int Position;

enum State{
    DEAD,
    ALIVE,
};

class Lattice;

class Cell{

    public:
        Cell();
        Cell(const Position&, const State&);
        ~Cell();

        State getState() const;
        State setState(State);

        int nextState(const Lattice&);
        void updateState();

    private:
        Position position_ = 0;
        State state_ = DEAD;
        State nextState_ = DEAD;

};

std::ostream& operator<<(std::ostream&, const Cell&);