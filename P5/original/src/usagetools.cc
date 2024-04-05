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
        Usage();
        throw std::invalid_argument("Falta el argumento para la opción -size");
      }
    } else if (arg == "-ord") {
      if (i + 1 < argc) {
        this->ordenationFunction = argv[i + 1];
        hasOrdenationFunction = true;
        ++i;
      } else {
        Usage();
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
            Usage();
            throw std::invalid_argument("Falta el argumento para la opción -init");
          }
        }
        i++;
      } else {
        Usage();
        throw std::invalid_argument("Falta el argumento para la opción -hash");
      }
    } else if (arg == "-trace") {
      if (i + 1 < argc) {
        this->traces = argv[i + 1];
        hasTraces = true;
        ++i;
      } else {
        Usage();
        throw std::invalid_argument("Falta el argumento para la opción -bs");
      }
    } else {
      Usage();
      throw std::invalid_argument("Opción desconocida");
    }
  }
  if (!hasTableSize || !hasInitSystem || !hasOrdenationFunction || !hasTraces) {
    Usage();
    throw std::invalid_argument("Faltan argumentos obligatorios");
  }
  if (this->initsystem == "file" && ( hasFile == false)) {
    Usage();
    throw std::invalid_argument("Faltan argumentos obligatorios");
  }
}

// Implementar la simulación en funcion de las opciones que se elijan
void Options::RunSimulation() {
  StaticSequence<NIF>* sequence;
  sequence = new StaticSequence<NIF>(this->tableSize);
  if (this->initsystem == "manual") {
    std::vector<NIF> values;
    for (unsigned i = 0; i < this->tableSize; i++) {
      std::cout << "Introduce el valor " << i + 1 << ": ";
      NIF value;
      std::cin >> value;
      values.push_back(value);
    }
    for (auto value : values) {
      sequence->insert(value);
    }
  } else if (this->initsystem == "random") {
    for (unsigned i = 0; i < this->tableSize; i++) {
      NIF value;
      sequence->insert(value);
    }
  } else if (this->initsystem == "file") {
    std::ifstream file(this->filename);
    if (!file.is_open()) {
      std::cerr << "Error al abrir el fichero\n";
      throw std::invalid_argument("Error al abrir el fichero");
    }
    NIF value;
    while (file >> value) {
      sequence->insert(value);
    }
    file.close();
  }

  std::cout << "Before sorting: ";
  for (int i = 0; i < sequence->getSize(); i++) {
    std::cout << (sequence->getData()[i]) << " ";
  }
  std::cout << std::endl;

  SortMethod<NIF>* selection;
  if (this->ordenationFunction == "quick") { //
    selection = new Quick<NIF>(sequence);
  } else if (this->ordenationFunction == "heap") { 
    selection = new Heap<NIF>(sequence);
  } else if (this->ordenationFunction == "selection") { //
    selection = new Selection<NIF>(sequence);
  } else if (this->ordenationFunction == "shell") { //
    selection = new Shell<NIF>(sequence);
  } else if (this->ordenationFunction == "radix") { //
    selection = new Radix<NIF>(sequence);
  } else if (this->ordenationFunction == "bin") {
    selection = new Bin<NIF>(sequence);
  } else if (this->ordenationFunction == "merge") {
    selection = new Merge<NIF>(sequence);
  } else {
    std::cerr << "Función de ordenación no válida\n";
    throw std::invalid_argument("Función de ordenación no válida");
  }

  selection->Sort();

  std::cout << "After sorting: ";
  for (int i = 0; i < sequence->getSize(); i++) {
    std::cout << (sequence->getData()[i]) << " ";
  }
  std::cout << std::endl;

  delete sequence;

}

// AFuncion que muestra el uso del programa
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


