//Practica 1 : Implementación de un autómata celular unidimensional
//Autor : <Jonathan Martínez Pérez>
//Correo : <alu0101254098@ull.edu.es>
//Archivo programparameters.cc

#include "programparameters.h"

// Función para procesar los parámetros del programa
ProgramParameters::ProgramParameters(int argc, char* argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);
    bool valid_option;
    const int minargc{5};
    for (unsigned i = 0; i < args.size(); ++i) {
        valid_option = false;
        if (args[i] == "-size") {
            if (++i < args.size()) {
                valid_option = true;
                size_received = true;
                if (std::stoi(args[i]) >= 0) {
                    size = std::stoi(args[i]);
                } else {
                    std::cerr << "Numero invalido" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        } else if (args[i] == "-border") {
            if (++i < args.size()) {
                valid_option = true;
                border_received = true;
                std::string border_arg = args[i];
                if (border_arg == "open") {
                    if (++i < args.size()) {
                        if (args[i] == "0") {
                            border = COLD;
                        } else if (args[i] == "1") {
                            border = HOT;
                        } else {
                            std::cerr << "Argumento invalido para frontera" << std::endl;
                            exit(EXIT_FAILURE);
                        }
                    } else {
                        std::cerr << "Argumento invalido para frontera" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                } else if (border_arg == "periodic") {
                    border = PERIODIC;
                } else {
                    std::cerr << "Frontera invalida" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        } else if (args[i] == "-init") {
            if (++i < args.size()) {
                valid_option = true;
                file_option = true;
                filename = args[i];
            } else {
                std::cerr << "Nombre de fichero mal proporcionado" << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if (args[i] == "-help") {
            valid_option = true;
            showhelp = true;
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
    /*
    std::cout << "¿Desea guardar la salida en un fichero? (s/n)" << std::endl;
    std::string output;
    std::cin >> output;
    if (output == "s") {
        outputbyfile_ = true;
        std::cout << "Nombre del fichero: ";
        std::cin >> outputf;
    }
    */
}

// Función para mostrar la ayuda del programa
void ProgramParameters::showHelp() const {
    std::cout << "Este programa corre un automata celular con la regla 110.\n"
              << "Puedes seguir cuantas interacciones quieras hasta presionar q y enter.\n"
              << "La estructura para ejecuta<r el programa seria:\n"
              << "./main -size <X> -border <open [0|1] | periodic> -init <file>\n"
              << "Size y border son obligatorios mientras que init es opcional\n"
              << "0 es frontera fria y 1 caliente, ademas podras usar -help para imprimir este mensaje\n" << std::endl;
}

// Función para ejecutar la simulación
void ProgramParameters::runSimulation() {
    if (this->sizeReceived() && this->borderReceived()) {
        std::cout << "Tamaño: " << this->getSize() << std::endl;
        if (this->getBorder() == COLD) {
            std::cout << "Frontera: " << "Fria" << std::endl;
        } else if (this->getBorder() == HOT) {
            std::cout << "Frontera: " << "Caliente" << std::endl;
        } else {
            std::cout << "Frontera: " << "Periodica" << std::endl;
        }
        if (this->fileOption()) {
            std::cout << "Archivo: " << this->getFilename() << std::endl;
            Lattice lattice(this->getSize(), this->getBorder(), this->getFilename());
            lattice.ShowIterations();
        } else {
            Lattice lattice(this->getSize(), this->getBorder());
            lattice.ShowIterations();
        }
    } else {
        std::cerr << "No se indicaron los parametros correctamente" << std::endl;
    }
}

