//Autor: Jonathan Martínez Pérez
//Fichero: usagetools.cc
#include <iostream>
#include <string>
#include <stdexcept>

#include "usagetools.h"

// Constructor de la clase Options para parsear los args
Options::Options(int argc, char* argv[]) {

  if (argc < 4) {
    std::cerr << "Faltan argumentos obligatorios.\n";
    Usage();
    throw std::invalid_argument("Faltan argumentos obligatorios.");
  }

  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "-size") {
      if (i + 1 < argc) {
        this->tableSize = std::stoi(argv[i + 1]);
        hasTableSize = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -size");
      }
    } else if (arg == "-ord") {
      if (i + 1 < argc) {
        this->ordenationFunction = argv[i + 1];
        hasOrdenationFunction = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -ord");
      }
    } else if(arg == "-init") {
      if (i + 1 < argc) {
        this->initsystem = argv[i + 1];
        hasInitSystem = true;
        if (this->initsystem == "file") {
          if (i + 2 < argc) {
            this->filename = argv[i + 2];
            hasFile = true;
            i++;
          } else {
            throw std::invalid_argument("Falta el argumento para la opción -init");
          }
        }
        i++;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -hash");
      }
    } else if (arg == "-trace") {
      if (i + 1 < argc) {
        this->traces = argv[i + 1];
        hasTraces = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -bs");
      }
    } else {
      throw std::invalid_argument("Opción desconocida");
    }
  }
  if (!hasTableSize || !hasInitSystem || !hasOrdenationFunction || !hasTraces) {
    throw std::invalid_argument("Faltan argumentos obligatorios");
  }
  if (this->initsystem == "file" && ( hasFile == false)) {
    throw std::invalid_argument("Faltan argumentos obligatorios");
  }
}

void Options::RunSimulation() {
  std::cout << "Tamaño de la tabla: " << this->tableSize << std::endl;
  std::cout << "Función de ordenación: " << this->ordenationFunction << std::endl;
  std::cout << "Sistema de inicialización: " << this->initsystem << std::endl;
  if (this->initsystem == "file") {
    std::cout << "Nombre del fichero: " << this->filename << std::endl;
  }
  std::cout << "Traces: " << this->traces << std::endl;
}

// AYUDA
void Options::Usage() const{
    std::cout << "Uso: ./main -size <tamaño> -ord <función de ordenación> -init <manual | ramdom | file> [filename] -trace <y | n>\n";
    std::cout << "Opciones:\n";
    std::cout << "  -size <tamaño> : Tamaño de la tabla\n";
    std::cout << "  -ord <función de ordenación> : Función de ordenación a utilizar\n";
    std::cout << "  -init <sistema de inicialización> : Sistema de inicialización de la tabla\n";
    std::cout << "  -trace <fichero de trazas> : y o n\n";
    std::cout << "Funciones de ordenación disponibles:\n";
    std::cout << "  - quicksort\n";
    std::cout << "  - heapsort\n";
    std::cout << "  - selectionsort\n";
    std::cout << "Sistemas de inicialización disponibles:\n";
    std::cout << "  - manual\n";
    std::cout << "  - random\n";
    std::cout << "  - file <nombre del fichero>\n";
    std::cout << "Ejemplo de uso:\n";
    std::cout << "  ./main -size 100 -ord quicksort -init random -trace n\n";
    std::cout << "  ./main -size 100 -ord quicksort -init file init.txt -trace y\n";
}

// Implementación de la función Menu
void Options::Menu() {
    char option;
    do {
        std::cout << "Menú:\n";
        std::cout << "1. Insertar valor en la tabla\n";
        std::cout << "2. Buscar valor en la tabla\n";
        std::cout << "3. Mostrar tabla\n";
        std::cout << "4. Insertar un numero o varios ramdom\n";
        std::cout << "5. Salir del menú\n";

        std::cout << "Seleccione una opción: ";
        std::cin >> option;

        switch(option) {
            case '1':
                break;
            case '5':
                std::cout << "Saliendo del menú...\n";
                break;
            default:
                std::cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
                break;
        }
    } while(option != '5');
}

