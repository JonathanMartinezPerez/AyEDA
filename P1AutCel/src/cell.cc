//Practica 1 : Implementación de un autómata celular unidimensional
//Autor : <Jonathan Martínez Pérez>
//Correo : <alu0101254098@ull.edu.es>
//Archivo cell.cc

#include "cell.h"

// Constructor por defecto de la clase Cell
Cell::Cell() {}

// Constructor de la clase Cell para crear una célula con una posición y un estado
Cell::Cell(const Position& pos, const State& st) : position_(pos), state_(st) {}

// Destructor de la clase Cell
Cell::~Cell() {}

// Métodos de acceso a los atributos de la clase Cell
State Cell::getState() const {
    return state_;
}

// Método para cambiar el estado de la célula
State Cell::setState(State st) {
    state_ = st;
    return st;
}

// Método para calcular el estado siguiente de la célula
int Cell::nextState(const Lattice& lattice) {
  State right = lattice.getCell(position_ + 1).getState();
  State left = lattice.getCell(position_ - 1).getState();
  nextState_ = static_cast<State>((state_ + right + state_ * right + left * state_ * right) % 2);
  return 0;
}

// Método para actualizar el estado de la célula
void Cell::updateState(){
    state_ = nextState_;
}

// Sobrecarga del operador de salida para imprimir el estado de la célula
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    //imprime el estado de la célula X si es Alive y " " si es Dead
    os << (cell.getState() == ALIVE ? "X" : " ");
    return os;
}


