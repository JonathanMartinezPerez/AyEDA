//Practica 2 : Implementación de un autómata celular bidimensional
//Autor : <Jonathan Martínez Pérez>
//Correo : <alu0101254098@ull.edu.es>
//Archivo lattice.cc

#include "lattice.h"

// Constructor de la cuadrícula con un ancho, alto y frontera
Lattice::Lattice(const int width, const int height, const Frontier& border) {
    border_ = border;
    // Verificar si se necesita ajustar el tamaño de la cuadrícula debido a la frontera
    int adjusted_width = width;
    int adjusted_height = height;
    if (border != NOFRONTIER) {
        adjusted_width += 2;
        adjusted_height += 2;
    } else {
        adjusted_width += 4;
        adjusted_height += 4;
    }
    
    // Inicializar la cuadrícula con células muertas
    cells_.resize(adjusted_height);
    for (int i = 0; i < adjusted_height; ++i) {
        cells_[i].resize(adjusted_width);
        for (int j = 0; j < adjusted_width; ++j) {
            cells_[i][j] = new Cell(Position{j, i}, DEAD);
        }
    }

    // Preguntar al usuario qué células deben estar vivas
    int y;
    std::cout << "Ingrese las posiciones de las células vivas (x y), y finalice con -1 -1:\n";
    while (true) {
        std::string input;
        std::cin >> input;
        if (input == "q")
            break;
        int x = std::stoi(input);
        std::cin >> y;
        if (x >= 0 && x < adjusted_width && y >= 0 && y < adjusted_height)
            cells_[y][x]->setState(ALIVE); // Establecer célula viva
    }

    // Inicializar las células de la frontera según el tipo de frontera
    if (border != NOFRONTIER) {
        for (int i = 0; i < adjusted_height; ++i) {
            for (int j = 0; j < adjusted_width; ++j) {
                if (i == 0 || i == adjusted_height - 1 || j == 0 || j == adjusted_width - 1) {
                    // Célula en la frontera
                    if (border == COLD) {
                        // Frontera fría: todas las células de la frontera a 0
                        if (i == 0 || i == adjusted_height - 1 || j == 0 || j == adjusted_width - 1)
                            cells_[i][j] = new Cell(Position{j, i}, DEAD);
                    } else if (border == HOT) {
                        if (i == 0 || i == adjusted_height - 1 || j == 0 || j == adjusted_width - 1)
                            cells_[i][j] = new Cell(Position{j, i}, ALIVE);
                    }  else if (border == PERIODIC) {
                        // Frontera periódica: extremos del retículo son adyacentes
                        int ni = (i == 0) ? adjusted_height - 2 : (i == adjusted_height - 1) ? 1 : i;
                        int nj = (j == 0) ? adjusted_width - 2 : (j == adjusted_width - 1) ? 1 : j;
                        cells_[i][j] = new Cell(Position{nj, ni}, cells_[ni][nj]->getState());
                    } else if (border == REFLECTIVE) {
                        // Frontera reflectante
                        int ni = i;
                        int nj = j;

                        // Reflejar en el eje X
                        if (i == 0) ni = 1;
                        if (i == adjusted_height - 1) ni = adjusted_height - 2;

                        // Reflejar en el eje Y
                        if (j == 0) nj = 1;
                        if (j == adjusted_width - 1) nj = adjusted_width - 2;

                        // Asignar el estado de la célula adyacente al borde dentro del retículo
                        cells_[i][j] = new Cell(Position{nj, ni}, cells_[ni][nj]->getState());
                    }
                }
            }
        }
    }
    this->width_ = adjusted_width;
    this->height_ = adjusted_height;
}

// Constructor de la cuadrícula desde un archivo
Lattice::Lattice(const char* filename, const Frontier& border) {
    border_ = border;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }

    int rows, cols;
    file >> rows >> cols;

    // Verificar si se necesita ajustar el tamaño de la cuadrícula debido a la frontera
    int adjusted_width = cols;
    int adjusted_height = rows;
    if (border != NOFRONTIER) {
        adjusted_width += 2;
        adjusted_height += 2;
    } else {
        adjusted_width += 4;
        adjusted_height += 4;
    }
    // Inicializar la cuadrícula con células muertas
    cells_.resize(adjusted_height, std::vector<Cell*>(adjusted_width, nullptr));

    // Leer el contenido del archivo y configurar las células según su estado
    for (int i = 0; i < rows; ++i) {
        std::string row_data;
        file >> row_data;

        for (int j = 0; j < cols; ++j) {
            char state_char = row_data[j];
            int x = border != NOFRONTIER ? j + 1 : j;
            int y = border != NOFRONTIER ? i + 1 : i;

            if (state_char == '1')
                cells_[y][x] = new Cell(Position(x, y), ALIVE);
            else
                cells_[y][x] = new Cell(Position(x, y), DEAD);
        }
    }

    // Inicializar las células de la frontera según el tipo de frontera
    if (border != NOFRONTIER) {
        for (int i = 0; i < adjusted_height; ++i) {
            for (int j = 0; j < adjusted_width; ++j) {
                if (i == 0 || i == adjusted_height - 1 || j == 0 || j == adjusted_width - 1) {
                    // Célula en la frontera
                    if (border == COLD) {
                        // Frontera fría: todas las células de la frontera a 0
                        if (i == 0 || i == adjusted_height - 1 || j == 0 || j == adjusted_width - 1)
                            cells_[i][j] = new Cell(Position{j, i}, DEAD);
                    } else if (border == HOT) {
                        if (i == 0 || i == adjusted_height - 1 || j == 0 || j == adjusted_width - 1)
                            cells_[i][j] = new Cell(Position{j, i}, ALIVE);
                    }  else if (border == PERIODIC) {
                        // Frontera periódica: extremos del retículo son adyacentes
                        int ni = (i == 0) ? adjusted_height - 2 : (i == adjusted_height - 1) ? 1 : i;
                        int nj = (j == 0) ? adjusted_width - 2 : (j == adjusted_width - 1) ? 1 : j;
                        cells_[i][j] = new Cell(Position{nj, ni}, cells_[ni][nj]->getState());
                    } else if (border == REFLECTIVE) {
                        // Frontera reflectante
                        int ni = i;
                        int nj = j;

                        // Reflejar en el eje X
                        if (i == 0) ni = 1;
                        if (i == adjusted_height - 1) ni = adjusted_height - 2;

                        // Reflejar en el eje Y
                        if (j == 0) nj = 1;
                        if (j == adjusted_width - 1) nj = adjusted_width - 2;

                        // Asignar el estado de la célula adyacente al borde dentro del retículo
                        cells_[i][j] = new Cell(Position{nj, ni}, cells_[ni][nj]->getState());
                    }
                }
            }
        }
    }
    this->width_ = adjusted_width;
    this->height_ = adjusted_height;
    file.close();
}

// Destructor de la cuadrícula
Lattice::~Lattice() {
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            delete cells_[i][j];
        }
    }
}

// Devuelve la célula en una posición dada
const Cell& Lattice::getCell(const Position& pos) const {
    return *cells_[pos.second][pos.first];
}

// Devuelve todas las células
const std::vector<std::vector<Cell*>>& Lattice::getCells() const {
    return cells_;
}

// Devuelve el ancho de la cuadrícula
int Lattice::getWidth() const {
    return width_;
}

// Devuelve el alto de la cuadrícula
int Lattice::getHeight() const {
    return height_;
}

// Muestra el estado de la cuadrícula
void Lattice::ShowIterations() {
    unsigned iteration = 0;
    std::cout << "Tamaño del tablero " << width_ - 4 << "x" << height_ - 4 << std::endl;
    std::cout << "Population: " << Population() << std::endl;
    std::cout << "Iteracion: " << iteration++ << std::endl;
    std::cout << *this << std::endl;
    //mostrarMundo();
    std::cout << "🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨" << std::endl;
    // Calcular la siguiente generación y mostrarla cada vez que se pulse intro salir con q
    while (true) {
        startGeneration();
        std::cout << "Tamaño del tablero " << height_ - 4 << "x" << width_ - 4 << std::endl;
        std::cout << "Population: " << Population() << std::endl;
        std::cout << "Iteracion: " << iteration++ << std::endl;
        std::cout << *this << std::endl;
        if (std::cin.get() == 'q') {
            break;
        }
    }
    std::cout << std::endl;
}

// Dependiendo del borde escogemos
void Lattice::startGeneration() {
    switch (border_) {
        case REFLECTIVE:
            nextGenerationReflective();
            break;
        case PERIODIC:
            nextGenerationPeriodic();
            break;
        case NOFRONTIER:
            nextGenerationNoFrontier();
            break;
        default:
            nextGenerationOpen();
            break;
    }
}

// Calcula la siguiente generación de células para reflectante
void Lattice::nextGenerationReflective() {
    this->calculateNextState();
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (y == 0 || y == height_ - 1 || x == 0 || x == width_ - 1) {
                // Frontera reflectante
                int ni = y;
                int nj = x;

                // Reflejar en el eje X
                if (y == 0) ni = 1;
                if (y == height_ - 1) ni = height_ - 2;

                // Reflejar en el eje Y
                if (x == 0) nj = 1;
                if (x == width_ - 1) nj = width_ - 2;

                // Asignar el estado de la célula adyacente al borde dentro del retículo
                cells_[y][x]->setState(cells_[ni][nj]->getState());
            }
        }
    }
}

// Calcula la siguiente generación de células para periódica
void Lattice::nextGenerationPeriodic() {
    this->calculateNextState();
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (y == 0 || y == height_ - 1 || x == 0 || x == width_ - 1) {
                // Frontera periódica: extremos del retículo son adyacentes
                int ni = (y == 0) ? height_ - 2 : (y == height_ - 1) ? 1 : y;
                int nj = (x == 0) ? width_ - 2 : (x == width_ - 1) ? 1 : x;
                cells_[y][x]->setState(cells_[ni][nj]->getState());
            }
        }
    }
}

// Calcula la siguiente generación de células para abierta tanto fria como caliente
void Lattice::nextGenerationOpen() {
    this->calculateNextStateWithOutFrontier();
}

// Calcula la siguiente generación de células para las celulas de dentro de la reticula
void Lattice::nextGenerationNoFrontier() {
    this->calculateNextStateWithOutFrontierNoPosition();
    // Comprobamos los cuatro lados exteriores de la frontera
    // Si un lado tiene alguna viva, hay que añadir una fila o columna de muertas con front() o push() en ese lado
    // Si std::vector no actualiza, hay que hacer los metodos

    this->checkUpperBorder();
    this->checkLowerBorder();
    this->checkLeftBorder();
    this->checkRightBorder();
}

bool Lattice::checkUpperBorder() {
    bool check = false;
    for (int i = 1; i < width_ - 1; ++i) {
        if (this->cells_[1][i]->getState() == ALIVE) {
            check = true;
        }
    }
    if (check) {
        extendUpperBorder();
    } 
    return check;
}

void Lattice::extendUpperBorder() {
    this->cells_.insert(this->cells_.begin(), std::vector<Cell*>(width_, new Cell));
    this->height_++;
}

bool Lattice::checkLowerBorder() {
    bool check = false;
    for (int i = 1; i < width_ - 1; ++i) {
        if (this->cells_[height_ - 2][i]->getState() == ALIVE) {
            check = true;
        }
    }
    if (check) {
        extendLowerBorder();
    } 
    return check;
}

void Lattice::extendLowerBorder() {
    this->cells_.insert(this->cells_.end(), std::vector<Cell*>(width_, new Cell));
    this->height_++;
}

bool Lattice::checkLeftBorder() {
    std:: cout << "CheckLeftBorder" << std::endl;
    bool check = false;
    for (int i = 1; i < height_ - 1; ++i) {
        if (this->cells_[i][1]->getState() == ALIVE) {
            check = true;
        }
    }
    if (check) {
        extendLeftBorder();
    }
    return check;
}

void Lattice::extendLeftBorder() {
    std:: cout << "extendLeftBorder" << std::endl;
    for (int i = 0; i < height_; ++i) {
        this->cells_[i].insert(this->cells_[i].begin(), new Cell);
    }
    this->width_++;
    std:: cout << "extendLeftBorder CHECK" << std::endl;
}

bool Lattice::checkRightBorder() {
    bool check = false;
    for (int i = 1; i < height_ - 1; ++i) {
        if (this->cells_[i][width_ - 2]->getState() == ALIVE) {
            check = true;
        }
    }
    if (check) {
        extendRightBorder();
    } 
    return check;
}

void Lattice::extendRightBorder() {
    for (int i = 0; i < height_; ++i) {
        this->cells_[i].push_back(new Cell);
    }
    this->width_++;
}

void Lattice::calculateNextState() {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            Position pos(x, y);
            cells_[y][x]->nextState(*this);
        }   
    }

    // Actualizar el estado de las células en la cuadrícula
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            cells_[y][x]->updateState();
        }
    }
}

void Lattice::calculateNextStateWithOutFrontier() {
    for (int y = 1; y < height_ - 1; ++y) {
        for (int x = 1; x < width_ - 1; ++x) {
            Position pos(x, y);
            cells_[y][x]->nextState(*this); 
        }   
    }

    // Actualizar el estado de las células en la cuadrícula
    for (int y = 1; y < height_ - 1; ++y) {
        for (int x = 1; x < width_ - 1; ++x) {
            cells_[y][x]->updateState(); 
        }
    }
}

// Calcula la siguiente generación de
void Lattice::calculateNextStateWithOutFrontierNoPosition() {
    for (int y = 1; y < height_ - 1; ++y) {
        for (int x = 1; x < width_ - 1; ++x) {
            Position pos(x, y);
            cells_[y][x]->nextState(*this, y, x); 
        }   
    }

    // Actualizar el estado de las células en la cuadrícula
    for (int y = 1; y < height_ - 1; ++y) {
        for (int x = 1; x < width_ - 1; ++x) {
            cells_[y][x]->updateState(); 
        }
    }
}

// Devuelve el número de células vivas en la cuadrícula
std::size_t Lattice::Population() const {
    std::size_t population = 0;
    for (int y = 1; y < height_ - 1; ++y) {
        for (int x = 1; x < width_ - 1; ++x) {
            if (cells_[y][x]->getState() == ALIVE) {
                ++population;
            }
        }
    }
    return population;
}

// Sobrecarga del operador de inserción para imprimir la cuadrícula
std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
    for (int y = 0; y < lattice.getWidth() + 2; ++y) {
        os << "🟦";
    }
    os << std::endl;
    for (int y = 0; y < lattice.getHeight(); ++y) {
        os << "🟦";
        for (int x = 0; x < lattice.getWidth(); ++x)
            if (lattice.getCells()[y][x]->getState() == ALIVE) {
                os << "🟩";
            } else {
                os << "🟥";
            }
        os << "🟦" << std::endl;
    }
    for (int y = 0; y < lattice.getWidth() + 2; ++y) {
        os << "🟦";
    }
    return os << std::endl;
}
/*
// Sobrecarga del operador de inserción para imprimir la cuadrícula
std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
    os << "🟩" << std::endl;
    for (auto& row : lattice.getCells()) {
        os << "|";
        for (auto& cellPtr : row)
            os << *cellPtr;
        os << "|" << std::endl;
    }
    os << "-------------" << std::endl;
    return os;
}
*/
void Lattice::mostrarMundo() {
    std::cout << "-------------" << std::endl;
    for (int y = 2; y < height_ - 2; ++y) {
        std::cout << "|";
        for (int x = 2; x < width_ - 2; ++x) {
            std::cout << *cells_[y][x];
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "-------------" << std::endl;
}

// Sobrecarga del operador de acceso para obtener una célula en una posición dada
Cell& Lattice::operator[](const Position& pos) const{
    return *cells_[pos.second][pos.first];
}