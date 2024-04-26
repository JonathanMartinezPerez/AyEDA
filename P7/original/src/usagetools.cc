//Autor: Jonathan Martínez Pérez
//Fichero: usagetools.cc
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

#include "usagetools.h"

// Constructor de la clase Options para parsear los args
Options::Options(int argc, char* argv[]) {
  // Verificación de la cantidad mínima de argumentos
  if (argc < 5) {
    std::cerr << "Faltan argumentos obligatorios.\n";
    Usage();
    throw std::invalid_argument("Faltan argumentos obligatorios.");
  }
  // Iteración sobre los argumentos de la línea de comandos
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-ab") {
      // Verificación de existencia de argumento siguiente
      if (i + 1 < argc) {
        this->ab = argv[i + 1];
        hasAb = true;
        ++i;
      } else {
        Usage();
        throw std::invalid_argument("Falta el argumento para la opción -ab");
      }
    } else if (arg == "-init") {
      // Verificación de existencia de argumento siguiente
      if (i + 1 < argc) {
        this->initsystem = argv[i + 1];
        hasInitSystem = true;
        if (this->initsystem == "file") {
          // Verificación de existencia de argumento siguiente
          if (i + 3 < argc) {
            this->filename = argv[i + 2];
            this->quantity = std::stoi(argv[i + 3]);
            hasFile = true;
            hasQuantity = true;
            ++i;
            ++i;
          } else {
            Usage();
            throw std::invalid_argument("Falta el argumento para la opción -init");
          }
        } else if (this->initsystem == "random") {
          hasQuantity = true;
          if (i + 2 < argc) {
            this->quantity = std::stoi(argv[i + 2]);
            ++i;
          } else {
            Usage();
            throw std::invalid_argument("Falta el argumento para la opción -init");
          }
        } else if (this->initsystem == "manual") {
          hasQuantity = false;
        } else {
          Usage();
          throw std::invalid_argument("Opción desconocida");
        }
        ++i;
      } else {
        Usage();
        throw std::invalid_argument("Falta el argumento para la opción -init");
      }
    } else {
      Usage();
      throw std::invalid_argument("Opción desconocida");
    }
  }
  // Verificación de argumentos obligatorios
  if (!hasAb || !hasInitSystem) {
    Usage();
    throw std::invalid_argument("Faltan argumentos obligatorios");
  }
  // Verificación de argumentos para inicialización desde archivo
  if (this->initsystem == "file" && !hasFile) {
    Usage();
    throw std::invalid_argument("Falta el argumento obligatorio para la opción -init file");
  }
}


// Implementar la simulación en funcion de las opciones que se elijan
void Options::RunSimulation() {
  AB<NIF>* arbol;
  if (this->ab == "abb") {
    arbol = new ABB<NIF>;
  } else if (this->ab == "abe") {
    arbol = new ABE<NIF>;
  } else if (this->ab == "avl") {
    arbol = new AVL<NIF>;
  } else {
    Usage();
    throw std::invalid_argument("Opción desconocida");
  }

  if (this->initsystem == "manual") {
    std::cout << "Elegiste la opcion manual\n";
  } else if (this->initsystem == "random") {
      for (int i = 0; i < this->quantity; ++i){
        NIF nif;
        arbol->insertar(nif);
      }
  } else if (this->initsystem == "file") {
    std::ifstream file(this->filename);
    if (!file.is_open()) {
      std::cerr << "Error al abrir el fichero\n";
      throw std::invalid_argument("Error al abrir el fichero");
    }
    std::string line;
    while (std::getline(file, line)) {
      std::istringstream iss(line);
      std::string token;
      int count = 0;
      while (count < this->quantity && std::getline(iss, token, ' ')) {
          arbol->insertar(std::stoi(token));
          count++;
      }
    if (count >= this->quantity) {
        break;  // Stop reading if we have reached the desired quantity
    }
}
    file.close();
  } else {
    Usage();
    throw std::invalid_argument("Opción desconocida");
  }

  Menu(arbol);
}

// Función que muestra el menú de opciones
void Options::Menu(AB<NIF>* arbol) const {
    char option;
    do {
        std::cout << "[0] Salir \n";
        std::cout << "[1] Insertar clave\n";
        std::cout << "[2] Buscar clave\n";
        std::cout << "[3] Mostrar arbol inorden\n";

        std::cout << "Seleccione una opción: ";
        std::cin >> option;

        switch(option) {
            case '1':
                int key;
                std::cout << "Ingrese la clave a insertar: ";
                std::cin >> key;
                arbol->insertar(key);
                break;
            case '2':
                int searchKey;
                std::cout << "Ingrese la clave a buscar: ";
                std::cin >> searchKey;
                if (arbol->buscar(searchKey)) {
                    std::cout << "La clave " << searchKey << " está en el árbol.\n";
                } else {
                    std::cout << "La clave " << searchKey << " no está en el árbol.\n";
                }
                break;
            case '3':
                std::cout << "Mostrando árbol inorden:\n";
                arbol->inorden();
                break;
            case '0':
                std::cout << "Saliendo del menú...\n";
                break;
            default:
                std::cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
                break;
        }
    } while(option != '0');   

}

// AFuncion que muestra el uso del programa
void Options::Usage() const{
    std::cout << "Uso: ./main <-ab abb|abe> <-init manual|ramdom n|file filename n> \n";
}


