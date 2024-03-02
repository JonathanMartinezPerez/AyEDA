//Practica 3 : Automata celular general
//Autor : <Jonathan Martínez Pérez>
//Correo : <alu0101254098@ull.edu.es>
//Archivo cell.h

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cstdarg>
#include <stdexcept>
#include <ostream>

enum State{
    DEAD,
    ALIVE,
};

#include "lattice.h"

class Lattice;

class Cell {           
    public :
    
        Cell(const Position&, const State&);
        virtual ~Cell();

        State getState() const;
        void setState(const State&);

        virtual void nextState(const Lattice&) = 0;
        virtual void updateState();

        virtual std::ostream& display(std::ostream&) const = 0;
        friend std::ostream& operator<<(std::ostream&, const Cell&);

    protected:
        const Position& position;
        State state;
        State nextstate_;   
};

// Clase CellACE para autómata celular elemental
class CellACE : public Cell {
    public:
        CellACE(const Position&, const State&);

        virtual void nextState(const Lattice&) = 0;
        virtual std::ostream& display(std::ostream& os) const override;
};

// Clase CellLife para el juego de la vida
class CellLife : public Cell {
    public:

        CellLife(const Position&, const State&);

        virtual void nextState(const Lattice&) = 0;
        virtual std::ostream& display(std::ostream&) const override;
};

class CellAce110 : public CellACE {
    public:
        CellAce110(const Position&, const State&);
        virtual void nextState(const Lattice&) override;
};

class CellAce30 : public CellACE {
    public:
        CellAce30(const Position&, const State&);
        virtual void nextState(const Lattice&) override;
};

class CellLife23_3 : public CellLife {
    public:
        CellLife23_3(const Position&, const State&);
        virtual void nextState(const Lattice&) override;
};      

class CellLife51_346 : public CellLife {
    public:
        CellLife51_346(const Position&, const State&);
        virtual void nextState(const Lattice&) override;
};  

