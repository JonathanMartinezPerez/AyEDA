// Practica 2 : Implementación de un autómata celular bidimensional
// Autor : <Jonathan Martínez Pérez>
// Correo : <alu0101254098@ull.edu.es>
// Archivo programparameters.cc

#include "programparameters.h"

// Constructor de la clase ProgramParameters
ProgramParameters::ProgramParameters(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-size" && i + 2 < argc) {

            int width = std::stoi(argv[i + 1]);
            int height = std::stoi(argv[i + 2]);
            size = std::make_pair(width, height);
            size_received = true;
            i += 2;
        } else if (arg == "-init" && i + 1 < argc) {
            filename = argv[i + 1];
            file_option = true;
            i++;
        } else if (arg == "-border" && i + 1 < argc) {
            std::string border_type = argv[i + 1];
            if (border_type == "open" && i + 2 < argc) {
                    int open_value = std::stoi(argv[i+2]);
                    if (open_value == 0)
                        border = COLD;
                    else if (open_value == 1)
                        border = HOT; // 
                    border_received = true;
                    i += 2;
            } else if (border_type == "periodic")
                border = PERIODIC;
            else if (border_type == "reflective")
                border = REFLECTIVE;
            else if (border_type == "noborders")
                border = NOFRONTIER;
            border_received = true;
            break;
        } else if (arg == "-h" || arg == "--help") {
            showHelp_ = true;
            break;
        }
    }
}

// Método para empezar la simulación
void ProgramParameters::runSimulation() {
    if (showHelp_) {
        showHelp();
        return;
    }

    if (!border_received) {
        std::cerr << "Error: No se especifico frontera\n";
        return;
    }

    if (!size_received && !file_option) {
        std::cerr << "Error: No se ha provisto ni de init ni size.\n";
        return;
    }

    if (sizeReceived() && borderReceived()) {

        if (this->getBorder() == NOFRONTIER) {
            std::cout << "Tamaño: " << size.first + 2 << "x" << size.second + 2 << std::endl;
        }
        else {
            std::cout << "Tamaño: " << size.first << "x" << size.second << std::endl;
        }
        
        std::cout << "Frontera: ";
        switch (border) {
            case COLD:
                std::cout << "Fría" << std::endl;
                break;
            case HOT:
                std::cout << "Caliente" << std::endl;
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
        std::cout << "Frontera: " << this->getBorder() << std::endl;
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
              << "./main [-size <X> <Y>] -border <open[0|1]> <periodic> <reflective> <noborder> [-init <file>]\n"
              << "Size y init son excluyentes mientras que border es obligatorio\n"
              << "0 es frontera fria y 1 caliente, ademas podras usar -help para imprimir este mensaje\n" << std::endl;
}
