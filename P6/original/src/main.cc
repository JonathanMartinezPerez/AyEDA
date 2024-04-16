#include <iostream>

#include "AB.h"
#include "ABB.h"
#include "ABE.h"

int main() {
    int opcion;
    long clave;
    ABE<long> arbolEquilibrado;
    ABB<long> arbolBusqueda;

    do {
        std::cout << "Menú:" << std::endl;
        std::cout << "[0] Salir" << std::endl;
        std::cout << "[1] Insertar clave" << std::endl;
        std::cout << "[2] Buscar clave" << std::endl;
        std::cout << "[3] Mostrar árbol inorden" << std::endl;
        std::cout << "Ingrese una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 0:
                std::cout << "Saliendo..." << std::endl;
                break;
            case 1:
                std::cout << "Ingrese la clave a insertar: ";
                std::cin >> clave;
                arbolEquilibrado.insertar(clave);
                arbolBusqueda.insertar(clave);
                std::cout << "Árbol equilibrado después de la inserción:" << std::endl;
                std::cout << arbolEquilibrado << std::endl;
                std::cout << "Árbol de búsqueda después de la inserción:" << std::endl;
                std::cout << arbolBusqueda << std::endl;
                break;
            case 2:
                std::cout << "Ingrese la clave a buscar: ";
                std::cin >> clave;
                std::cout << "Buscar clave en árbol equilibrado: " << (arbolEquilibrado.buscar(clave) ? "Encontrado" : "No encontrado") << std::endl;
                std::cout << "Buscar clave en árbol de búsqueda: " << (arbolBusqueda.buscar(clave) ? "Encontrado" : "No encontrado") << std::endl;
                break;
            case 3:
                std::cout << "Árbol equilibrado en orden:" << std::endl;
                std::cout << arbolEquilibrado << std::endl;
                std::cout << "Árbol de búsqueda en orden:" << std::endl;
                std::cout << arbolBusqueda << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Por favor, seleccione una opción válida." << std::endl;
                break;
        }

    } while (opcion != 0);

    return 0;
}