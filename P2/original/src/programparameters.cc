// Practica 2 : Implementación de un autómata celular bidimensional
// Autor : <Jonathan Martínez Pérez>
// Correo : <alu0101254098@ull.edu.es>
// Archivo programparameters.cc

#include "programparameters.h"

// Constructor de la clase ProgramParameters
ProgramParameters::ProgramParameters(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Error: Argumentos insuficientes." << std::endl;
        showHelp();
        exit(EXIT_FAILURE);
    }
    std::vector<std::string> args(argv, argv + argc);
    size_received = false;
    border_received = false;
    file_option = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (args[i] == "-size") {
            if (i + 2 < argc) {
                if (!size_received) {
                    size_received = true;
                    std::cout << "Size received" << std::endl;
                    int rows = std::stoi(argv[i + 1]);
                    int cols = std::stoi(argv[i + 2]);
                    size = std::make_pair(rows, cols);
                    i += 2; 
                } else {
                    std::cerr << "Error: Se proporcionaron múltiples argumentos para -size." << std::endl;
                    exit(EXIT_FAILURE);
                }
            } else {
                std::cerr << "Error: Argumentos insuficientes para -size." << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if (args[i] == "-border") {
            if (i + 1 < argc) {
                if (!border_received) {
                    border_received = true;
                    std::string border_arg = argv[i + 1];
                    if (border_arg == "open") {
                        if (border_arg == "open" && i + 2 < argc) {
                            ++i;
                        }
                        if (i + 1 < argc) {
                            if (isdigit(argv[i + 1][0])) {
                                border = (argv[i + 1][0] == '0') ? COLD : HOT;
                            } else {
                                std::cerr << "Argumento inválido para -border." << std::endl;
                                exit(EXIT_FAILURE);
                            }
                        } else {
                            std::cerr << "Argumentos insuficientes para -border." << std::endl;
                            exit(EXIT_FAILURE);
                        }
                    } else {
                        std::cerr << "Frontera inválida." << std::endl;
                        exit(EXIT_FAILURE);
                    }
                } else {
                    std::string border_arg = argv[i + 1];
                    if (border_arg == "reflective") {
                        border = REFLECTIVE;
                    } else if (border_arg == "noborder") {
                        border = NOFRONTIER;
                    } else {
                        std::cerr << "Frontera inválida." << std::endl;
                        exit(EXIT_FAILURE);
                    }
                }
            } else {
                std::cerr << "Error: Argumentos insuficientes para -border." << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if (arg == "-init") {
            if (i + 1 < argc) {
                if (!file_option) {
                    file_option = true;
                    filename = argv[i + 1];
                    ++i;  // Skip the next argument
                } else {
                    std::cerr << "Error: Se proporcionaron múltiples argumentos para -init." << std::endl;
                    exit(EXIT_FAILURE);
                }
            } else {
                std::cerr << "Error: Argumentos insuficientes para -init." << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if (arg == "-help") {
            showHelp();
            exit(EXIT_SUCCESS);
        } else {
            std::cerr << "Error: Argumento inválido." << std::endl;
            showHelp();
            exit(EXIT_FAILURE);
        }
    }

    if (!border_received) {
        std::cerr << "Error: El parámetro -border es obligatorio." << std::endl;
        showHelp();
        exit(EXIT_FAILURE);
    }

    if (size_received && file_option) {
        std::cerr << "Error: Los parámetros -size e -init son excluyentes." << std::endl;
        showHelp();
        exit(EXIT_FAILURE);
    }
}

// Método para empezar la simulación
void ProgramParameters::runSimulation() {
    if (sizeReceived() && borderReceived()) {
        std::cout << "Tamaño: " << size.first << "x" << size.second << std::endl;
        std::cout << "Frontera: ";
        switch (border) {
            case COLD:
                std::cout << "Frontera fría" << std::endl;
                break;
            case HOT:
                std::cout << "Frontera caliente" << std::endl;
                break;
            case PERIODIC:
                std::cout << "Periódica" << std::endl;
                break;
            case REFLECTIVE:
                std::cout << "Reflectora" << std::endl;
                break;
            case NOFRONTIER:
                std::cout << "Sin Frontera" << std::endl;
                break;
        }
        Lattice lattice(this->getSize().first, this->getSize().second, this->getBorder());
        lattice.ShowIterations();

    } else if (this->fileOption()) {
        std::cout << "Archivo: " << this->getFilename() << std::endl;
        Lattice lattice(this->getFilename(), this->getBorder());
        lattice.ShowIterations();
    } else {
        std::cerr << "No se indicaron los parametros correctamente" << std::endl;
        showHelp();
    }
}

// Método para mostrar la ayuda del programa
void ProgramParameters::showHelp() const {
    std::cout << "Este programa corre un automata celular bidimensional.\n"
              << "Puedes seguir cuantas interacciones quieras hasta presionar q y enter.\n"
              << "La estructura para ejecutar el programa seria:\n"
              << "./main -size <X> <Y> -border <reflective | noborder> [-init <file>] [-help]\n"
              << "Size y init son excluyentes mientras que border es obligatorio\n"
              << "0 es frontera fria y 1 caliente, ademas podras usar -help para imprimir este mensaje\n" << std::endl;
}
