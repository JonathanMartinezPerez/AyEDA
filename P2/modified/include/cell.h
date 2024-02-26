//Practica 2 : Implementación de un autómata celular bidimensional
//Autor : <Jonathan Martínez Pérez>
//Correo : <alu0101254098@ull.edu.es>
//Archivo cell.h

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <utility>

#include "lattice.h"

typedef std::pair<int,int> Position;

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

        State nextState(const Lattice&);
        State nextState(const Lattice& lattice, int y, int x);
        void updateState();

    private:
        Position position_;
        State state_ = DEAD;
        State nextState_ = DEAD;
};

std::ostream& operator<<(std::ostream&, const Cell&);