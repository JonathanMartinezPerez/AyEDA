//Practica 2 : Implementación de un autómata celular bidimensional
//Autor : <Jonathan Martínez Pérez>
//Correo : <alu0101254098@ull.edu.es>
//Archivo programparameters.cc

#include "programparameters.h"

ProgramParameters::ProgramParameters(int argc, char* argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);
    bool valid_option;
    const int minargc{5};
    for (unsigned i = 0; i < args.size(); ++i) {
        valid_option = false;
        if (args[i] == "-size") {
            if (i + 2 < args.size()) { // Asegurar que hay suficientes argumentos para tamaño
                valid_option = true;
                size_received = true;
                int rows = std::stoi(args[i + 1]);
                int cols = std::stoi(args[i + 2]);
                size = std::make_pair(rows, cols); // Almacenar el tamaño como un par de enteros
                i += 2; // Avanzar a los próximos dos argumentos
            } else {
                std::cerr << "Argumentos insuficientes para -size" << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if (args[i] == "-border") {
            if (i + 1 < args.size()) {
                valid_option = true;
                border_received = true;
                std::string border_arg = args[i + 1];
                if (border_arg == "open") {
                    if (i + 2 < args.size()) {
                        if (args[i + 2] == "0") {
                            border = COLD;
                        } else if (args[i + 2] == "1") {
                            border = HOT;
                        } else {
                            std::cerr << "Argumento invalido para frontera" << std::endl;
                            exit(EXIT_FAILURE);
                        }
                    } else {
                        std::cerr << "Argumento invalido para frontera" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    i += 2; // Avanzar a los próximos dos argumentos
                } else if (border_arg == "periodic") {
                    border = PERIODIC;
                    ++i; // Avanzar al próximo argumento
                } else {
                    std::cerr << "Frontera invalida" << std::endl;
                    exit(EXIT_FAILURE);
                }
            } else {
                std::cerr << "Argumentos insuficientes para -border" << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if (args[i] == "-init") {
            // Código para procesar la opción -init...
        } else if (args[i] == "-help") {
            // Código para procesar la opción -help...
        }
        if (!valid_option) {
            std::cerr << args[i] << " no es valido" << std::endl;
            std::cerr << "Para imprimir ayuda " << argv[0] << " -help" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    if (argc > 1) {
        std::string param1 = argv[1];
        if (param1 == "-help") {
            showHelp();
            exit(EXIT_SUCCESS);
        }
    }
    if (argc >= minargc) {
        std::cout << "El programa lleva a cabo la simulacion de un automata celular con la regla 110\n"
                  << "Pulsar q y enter para finalizar" << std::endl;
    } else {
        std::cerr << "Los parametros no son suficientes o incorrectos" << argv[0] << "--help" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void ProgramParameters::runSimulation() {
    if (this->sizeReceived() && this->borderReceived()) {
        std::cout << "Tamaño: " << this->getSize().first << "x" << this->getSize().second << std::endl;
        std::cout << "Frontera: " << this->getBorder() << std::endl;
        

    } else {
        std::cerr << "No se indicaron los parámetros correctamente" << std::endl;
    }
}

void ProgramParameters::showHelp() const {
    std::cout << "Este programa corre un automata celular con la regla 110.\n"
              << "Puedes seguir cuantas interacciones quieras hasta presionar q y enter.\n"
              << "La estructura para ejecutar el programa seria:\n"
              << "./main -size <X> <Y> -border <open [0|1] | periodic> -init <file>\n"
              << "Size y border son obligatorios mientras que init es opcional\n"
              << "0 es frontera fria y 1 caliente, ademas podras usar -help para imprimir este mensaje\n" << std::endl;
}
