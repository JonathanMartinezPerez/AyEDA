//Practica 2 : Implementación de un autómata celular bidimensional
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

// Método para calcular el estado siguiente de la célula Regla 110
State Cell::nextState(const Lattice& lattice) {
    int aliveNeighbors = 0;

    // Coordenadas relativas de las células vecinas
    int neighborOffsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };

    // Obtener las coordenadas de la célula actual
    int y = position_.second;
    int x = position_.first;

    // Contar el número de células vivas vecinas
    for (int i = 0; i < 8; ++i) {
        int ny = y + neighborOffsets[i][0]; // Cambiado de nx a ny y viceversa
        int nx = x + neighborOffsets[i][1]; // Cambiado de ny a nx y viceversa

        // Verificar si la célula vecina está dentro de los límites de la cuadrícula
        if (nx >= 0 && nx < lattice.getWidth() && ny >= 0 && ny < lattice.getHeight()) {
            if (lattice.getCell({nx, ny}).getState() == ALIVE) { // Cambiado el orden de las coordenadas
                ++aliveNeighbors;
            }
        }
    }

    // Determinar el estado siguiente según las reglas del juego de la vida
    if (state_ == ALIVE) {
        if (aliveNeighbors < 2 || aliveNeighbors > 3) {
            return DEAD;
        }
    } else {
        if (aliveNeighbors == 3) {
            return ALIVE;
        }
    }
    return state_;
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


