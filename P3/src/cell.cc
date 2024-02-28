#include "cell.h"

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

CellAce100::CellAce100(const Position& p, const State& s): CellACE(p, s) {}

void CellAce100::nextState(const Lattice& l) {
    int n = 0;
    for (int i = -1; i <= 1; i++) {
        if (l.getCell(PositionDim<1>(1, position[0] + i)) == ALIVE) {
            n++;
        }
    }
    if (n == 1) {
        state = ALIVE;
    } else {
        state = DEAD;
    }
}