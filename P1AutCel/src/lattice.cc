    //Practica 1 : Implementación de un autómata celular unidimensional
    //Autor : <Jonathan Martínez Pérez>
    //Correo : <alu0101254098@ull.edu.es>
    //Archivo lattice.cc

    #include "lattice.h"

    // Constructor de la clase Lattice para crear la malla de células
    Lattice::Lattice(const int size, const Frontier& frontier) {
        size_ = size + 2;
        cells_.resize(size_);
        border_ = frontier;
        State state;
        for (int i = 0; i < size + 2; ++i) {
            state = DEAD;
            if (i == size / 2) {
                state = ALIVE;
            }
            if (i == 0 || i == size + 1) {
                if (border_ == HOT) {
                    state = ALIVE;
                } 
            } 
            cells_[i] = new Cell(i, state);
        }
        if (border_ == PERIODIC) {
            cells_[0] -> setState(cells_[size_ - 2] -> getState());
            cells_[size_ - 1] -> setState(cells_[1] -> getState());  
        } 
    }

    // Constructor de la clase Lattice para crear la malla de células a partir de un archivo
    Lattice::Lattice(const int size, const Frontier& frontier, const std::string& file) {
        std::ifstream input_file{file};
        if (input_file.is_open()) {
        std::vector<int> stcells;
        std::string line;
        while (std::getline(input_file, line)) {
        std::istringstream iss(line);
        int num;
            while (iss >> num) {
                stcells.emplace_back(num);
            }
        }
        std::cout << std::endl;
        if (stcells.size() != static_cast<unsigned>(size)) {
            std::cerr << "El tamaño especificado no coindice con el numero de cells en la file" << file << "." << std::endl; 
            exit(EXIT_FAILURE);
        }
        size_ = size + 2;
        cells_.resize(size_);
        border_ = frontier;
        State state;
        for (int i = 0, j = 0; i < size + 2; ++i) {
            state = DEAD;
            if (i == 0 || i == size + 1) {
            if (border_ == HOT) {
                state = ALIVE;
            } 
            } else {
            state = static_cast<State>(stcells[j++]);
            }
            cells_[i] = new Cell(i, state);
        }
        if (border_ == PERIODIC) {
            cells_[0] -> setState(cells_[size_ - 2] -> getState());
            cells_[size_ - 1] -> setState(cells_[1] -> getState());  
        } 
        } else {
            std::cerr << "Error al abrir el archivo" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // Destructor de la clase Lattice
    Lattice::~Lattice() {
        // Liberación de memoria
        for (long unsigned int i = 0; i < cells_.size(); i++) {
            delete cells_[i];
        }
    }

    // Obtención de una célula
    const Cell& Lattice::getCell(const Position& pos) const {
        return *cells_[pos];
    }

    // Obtención de todas las células
    const std::vector<Cell*>& Lattice::getCells() const {
        return cells_;
    }

    // Cálculo de la siguiente iteración
    void Lattice::nextGeneration() {
        for (int i = 1; i < size_ - 1; ++i) {
            cells_[i] -> nextState(*this); 
        } 
        for (int i = 1; i < size_ - 1; ++i) {
            cells_[i] -> updateState(); 
        } 
        if (border_ == PERIODIC) {
            cells_[0] -> setState(cells_[size_ - 2] -> getState());
            cells_[size_ - 1] -> setState(cells_[1] -> getState());  
        } 
    }

    // Mostrar las iteraciones
    void Lattice::ShowIterations() {
        unsigned iteration = 0;
        std::cout << "Iteracion: " << iteration++ << "\t\t| ";
        for (const Cell* cellPtr : cells_) {
            std::cout << *cellPtr;
        }
        std::cout << " |" << std::endl;

        while (true) {
            nextGeneration();
            std::cout << "Iteracion: " << iteration++ << "\t\t| ";
            for (const Cell* cellPtr : cells_) {
                std::cout << *cellPtr;
            }
            std::cout << " |";
            if (std::cin.get() == 'q') {
                break;
            }
        }
    }

    // Sobrecarga del operador de salida
    std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
        for (const Cell* cellPtr : lattice.cells_) {
            os << *cellPtr; // Desreferenciar el puntero y imprimir la célula
        }
        return os;
    }
