//Practica 1 : Implementación de un autómata celular unidimensional
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
    int getSize() const { return size; }
    bool borderReceived() const { return border_received; }
    Frontier getBorder() const { return border; }
    bool fileOption() const { return file_option; }
    std::string getFilename() const { return filename; }
    bool outputbyfile() const { return outputbyfile_; }
    std::string nameoutputf() const { return outputf; } 

private:
    bool showhelp = false;
    bool size_received = false;
    int size;
    bool border_received = false;
    Frontier border = COLD;
    bool file_option = false;
    std::string filename;
    bool outputbyfile_ = false;
    std::string outputf;
};


