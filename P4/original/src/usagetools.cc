//usagetools.cc
#include <iostream>
#include <string>
#include <stdexcept>

#include "usagetools.h"

DispersionFunction<NIF>* dispersionFunctionInstance;
ExplorationFunction<NIF>* explorationFunctionInstance;

Options::Options(int argc, char* argv[]) {
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
        this->tableSize = std::stoi(argv[i + 1]);
        hasTableSize = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -ts");
      }
    } else if (arg == "-fd") {
      if (i + 1 < argc) {
        this->dispersionFunction = argv[i + 1];
        hasDispersionFunction = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -fd");
      }
    } else if(arg == "-hash") {
      if (i + 1 < argc) {
        this->hashType = argv[i + 1];
        hasHashType = true;
        if (this->hashType == "close") {
          hasBlockSize = true;
          hasExplorationFunction = true;
        }
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -hash");
      }
    } else if (arg == "-bs" && hasHashType == true) {
      if (i + 1 < argc) {
        this->blockSize = std::stoi(argv[i + 1]);
        hasBlockSize = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -bs");
      }
    } else if (arg == "-fe" && hasHashType == true) {
      if (i + 1 < argc) {
        this->explorationFunction = argv[i + 1];
        hasExplorationFunction = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -fe");
      }
    } else {
      throw std::invalid_argument("Opción desconocida");
    }
  }
  if (!hasTableSize || !hasDispersionFunction || !hasHashType) {
    throw std::invalid_argument("Faltan argumentos obligatorios");
  }
  if (this->hashType == "open" && (hasBlockSize || hasExplorationFunction)) {
    throw std::invalid_argument("Faltan argumentos obligatorios");
  }
}

void Options::RunSimulation() {
  if (this->hashType == "open") {
    if (this->dispersionFunction == "mod") {
      dispersionFunctionInstance = new ModuleDispersion<NIF>(this->tableSize);
    } else if (this->dispersionFunction == "sum") {
      dispersionFunctionInstance = new SumDispersion<NIF>(this->tableSize);
    } else if (this->dispersionFunction == "ramdom") {
      dispersionFunctionInstance = new PseudorandomDispersion<NIF>(this->tableSize);
    } else {
      std::cerr << "Función de dispersión no válida.\n";
      Usage();
      throw std::invalid_argument("Función de dispersión no válida.");
    }
    hashTable_d = new HashTable<NIF, DynamicSequence<NIF>>(this->tableSize, *dispersionFunctionInstance);
  } else if (this->hashType == "close"){
    if (this->dispersionFunction == "mod") {
      dispersionFunctionInstance = new ModuleDispersion<NIF>(this->tableSize);
    } else if (this->dispersionFunction == "sum") {
      dispersionFunctionInstance = new SumDispersion<NIF>(this->tableSize);
    } else if (this->dispersionFunction == "ramdom") {
      dispersionFunctionInstance = new PseudorandomDispersion<NIF>(this->tableSize);
    } else {
      std::cerr << "Función de dispersión no válida.\n";
      Usage();
      throw std::invalid_argument("Función de dispersión no válida.");
    }
    if (this->explorationFunction == "linear") {
      explorationFunctionInstance = new LinearExploration<NIF>;
    } else if (this->explorationFunction == "quadratic") {
      explorationFunctionInstance = new QuadraticExploration<NIF>;
    } else if (this->explorationFunction == "double") {
      explorationFunctionInstance = new DoubleHashingExploration<NIF>(*dispersionFunctionInstance);
    } else if (this->explorationFunction == "rehash") {
      explorationFunctionInstance = new RehashingExploration<NIF>(*dispersionFunctionInstance);
    } else {
      std::cerr << "Función de exploración no válida.\n";
      Usage();
      throw std::invalid_argument("Función de exploración no válida.");
    }
    hashTable = new HashTable<NIF, StaticSequence<NIF>>(this->tableSize, *dispersionFunctionInstance, *explorationFunctionInstance, this->blockSize);
  }
  Menu();
}

void Options::Usage() const{
    std::cout << "Uso: ./hashTable -ts <s> -fd <f> -hash <open|close> -bs <s> -fe <f>\n";
    std::cout << "-ts <s> : tamaño de la tabla\n";
    std::cout << "-fd <f> : función de dispersión -> sum, random o mod\n";
    std::cout << "-hash <open|close> : técnica de dispersión\n";
    std::cout << "-bs <s> : tamaño del bloque para dispersión cerrada\n";
    std::cout << "-fe <f> : función de exploración para dispersión cerrada -> linear, quadratic o double\n";
}

void Options::Menu() {
    char option;
    do {
        std::cout << "Menú:\n";
        std::cout << "1. Insertar valor en la tabla\n";
        std::cout << "2. Buscar valor en la tabla\n";
        std::cout << "3. Mostrar tabla\n";
        std::cout << "4. Salir del menú\n";

        std::cout << "Seleccione una opción: ";
        std::cin >> option;

        switch(option) {
            case '1':
                if (this->hashType == "open") {
                    NIF nif;
                    std::cout << "Introduzca el NIF a insertar: ";
                    std::cin >> nif;
                    hashTable_d->insert(nif);
                } else {
                    NIF nif;
                    std::cout << "Introduzca el NIF a insertar: ";
                    std::cin >> nif;
                    hashTable->insert(nif);
                }
                break;
            case '2':
                if (this->hashType == "open") {
                    NIF nif;
                    std::cout << "Introduzca el NIF a buscar: ";
                    std::cin >> nif;
                    if (hashTable_d->search(nif)) {
                        std::cout << "El NIF " << nif << " está en la tabla.\n";
                    } else {
                        std::cout << "El NIF " << nif << " no está en la tabla.\n";
                    }
                } else {
                    NIF nif;
                    std::cout << "Introduzca el NIF a buscar: ";
                    std::cin >> nif;
                    if (hashTable->search(nif)) {
                        std::cout << "El NIF " << nif << " está en la tabla.\n";
                    } else {
                        std::cout << "El NIF " << nif << " no está en la tabla.\n";
                    }
                }
                break; // Añadido el break para evitar la ejecución de los casos siguientes
            case '3':
                if (this->hashType == "open") {
                    hashTable_d->display();
                } else {
                    hashTable->display();
                }
                break; // Añadido el break para evitar la ejecución de los casos siguientes
            case '4':
                std::cout << "Saliendo del menú...\n";
                break;
            default:
                std::cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
                break;
        }
    } while(option != '4');
}

