#include <iostream>
#include <vector>
#include <random>
#include "insertion.h"

// Función para generar valores aleatorios
std::vector<long> generateRandomSequence(int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long> dis(1000, 9999);
    std::vector<long> seq(size);
    for (int i = 0; i < size; ++i) {
        seq[i] = dis(gen);
    }
    return seq;
}

int main() {
    int N;
    char choice;
    std::cout << "Ingrese el tamaño de la secuencia (N): ";
    std::cin >> N;

    std::cout << "¿Desea introducir los valores manualmente? (y/n): ";
    std::cin >> choice;

    std::vector<long> sequence;

    if (choice == 'y' || choice == 'Y') {
        std::cout << "Ingrese " << N << " valores separados por espacios: ";
        sequence.resize(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> sequence[i];
        }
    } else {
        sequence = generateRandomSequence(N);
        std::cout << "Secuencia generada aleatoriamente:" << std::endl;
        for (int num : sequence) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Seleccione el algoritmo de ordenación:" << std::endl;
    std::cout << "1. Inserción" << std::endl;
    int choice_algo;
    std::cin >> choice_algo;

    SortMethod<long>* sorter;

    switch (choice_algo) {
        case 1:
            sorter = new Insertion<long>(sequence);
            break;
        default:
            std::cout << "Opción no válida." << std::endl;
            return 1;
    }

    std::cout << "Secuencia ordenada:" << std::endl;
    sorter->Sort();
    for (long num : sequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
