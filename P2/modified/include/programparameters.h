//Practica 2 : Implementación de un autómata celular bidimensional
//Autor : <Jonathan Martínez Pérez>
//Correo : <alu0101254098@ull.edu.es>
//Archivo programparameters.h

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "lattice.h"

class ProgramParameters {
    public:
        ProgramParameters(int argc, char* argv[]);

        void runSimulation();
        void showHelp() const;
        
        bool sizeReceived() const { return size_received; }
        std::pair<int, int> getSize() const { return size; }
        bool borderReceived() const { return border_received; }
        Frontier getBorder() const { return border; }
        bool fileOption() const { return file_option; }
        char* getFilename() const { return filename; }

    private:
        bool showHelp_ = false;
        bool size_received = false;
        std::pair<int, int> size;
        bool border_received = false;
        Frontier border = COLD;
        bool file_option = false;
        char* filename;
};



