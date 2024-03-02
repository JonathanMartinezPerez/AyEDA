#include "../include/cell.h"

Cell::Cell(const Position& p, const State& s): position(p), state(s) {}

Cell::~Cell() {}

State Cell::getState() const {
    return state;
}

void Cell::setState(const State& s) {
    state = s;
}

void Cell::updateState() {
}

std::ostream& operator<<(std::ostream& os, const Cell& c) {
    return c.display(os);
}

CellACE::CellACE(const Position& p, const State& s): Cell(p, s) {}

std::ostream& CellACE::display(std::ostream& os) const {
    if (state == ALIVE) {
        os << "X";
    } else {
        os << " ";
    }
    return os;
}

CellLife::CellLife(const Position& p, const State& s): Cell(p, s) {}

std::ostream& CellLife::display(std::ostream& os) const {
    if (state == ALIVE) {
        os << "X";
    } else {
        os << " ";
    }
    return os;
}

CellAce110::CellAce110(const Position& p, const State& s): CellACE(p, s) {}

void CellAce110::nextState(const Lattice& l) {
    
    int left = l[PositionDim<1>(position[0] - 1)].getState();
    int right = l[PositionDim<1>(position[0] + 1)].getState();

    // Calcular el próximo estado de la célula 110
    nextstate_ = static_cast<State>((state + right + state * right + left * state * right) % 2);
}

CellAce30::CellAce30(const Position& p, const State& s): CellACE(p, s) {}

void CellAce30::nextState(const Lattice& l) {

    int left = l[PositionDim<1>(position[0] - 1)].getState();
    int right = l[PositionDim<1>(position[0] + 1)].getState();

    // Calcular el próximo estado de la célula regla 30
    nextstate_ = static_cast<State>((left + state + right + state * right) % 2);
}

CellLife23_3::CellLife23_3(const Position& p, const State& s): CellLife(p, s) {}

void CellLife23_3::nextState(const Lattice& l) {
    int alive = 0;
    for (int i = -1; i <= 1; i++) {
        alive += l[PositionDim<2>(position[0] - 1, position[1] + i)].getState();
        alive += l[PositionDim<2>(position[0] + 1, position[1] + i)].getState();
    }
    alive += l[PositionDim<2>(position[0], position[1] - 1)].getState();
    alive += l[PositionDim<2>(position[0], position[1] + 1)].getState();

    if (state == ALIVE) {
        if (alive == 2 || alive == 3) {
            state = DEAD;
        }
    } else {
        if (alive == 3) {
            state = ALIVE;
        }
    }
}



