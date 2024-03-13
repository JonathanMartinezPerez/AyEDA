//usagetools.cc
#include "../include/usagetools.h"

#include <iostream>
#include <string>
#include <stdexcept>

void Usage() {
    std::cout << "Uso: ./hashTable -ts <s> -fd <f> -hash <open|close> -bs <s> -fe <f>\n";
    std::cout << "-ts <s> : tamaño de la tabla\n";
    std::cout << "-fd <f> : función de dispersión -> sum, random o mod\n";
    std::cout << "-hash <open|close> : técnica de dispersión\n";
    std::cout << "-bs <s> : tamaño del bloque para dispersión cerrada\n";
    std::cout << "-fe <f> : función de exploración para dispersión cerrada -> linear, quadratic o double\n";
}

Options ParseArguments(int argc, char* argv[]) {
  Options options;
  bool hasTableSize = false;
  bool hasDispersionFunction = false;
  bool hasHashType = false;
  bool hasBlockSize = false;
  bool hasExplorationFunction = false;

  if (argc < 4) {
    std::cerr << "Faltan argumentos obligatorios.\n";
    Usage();
    throw std::invalid_argument("Faltan argumentos obligatorios.");
  }

  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "-ts") {
      if (i + 1 < argc) {
        options.tableSize = std::stoi(argv[i + 1]);
        hasTableSize = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -ts");
      }
    } else if (arg == "-fd") {
      if (i + 1 < argc) {
        options.dispersionFunction = argv[i + 1];
        hasDispersionFunction = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -fd");
      }
    } else if(arg == "-hash") {
      if (i + 1 < argc) {
        options.hashType = argv[i + 1];
        hasHashType = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -hash");
      }
    } else if (arg == "-bs") {
      if (i + 1 < argc) {
        options.blockSize = std::stoi(argv[i + 1]);
        hasBlockSize = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -bs");
      }
    } else if (arg == "-fe") {
      if (i + 1 < argc) {
        options.explorationFunction = argv[i + 1];
        hasExplorationFunction = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción " + arg);
      }
    } else {
      throw std::invalid_argument("Opción desconocida");
    }
  }
  if (!hasTableSize || !hasDispersionFunction || !hasHashType) {
    throw std::invalid_argument("Faltan argumentos oobligatorios");
  }
  return options;
}