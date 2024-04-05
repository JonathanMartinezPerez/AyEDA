//Autor: Jonathan Martínez Pérez
//Fichero: library.h
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

extern bool wantTrace;

inline void modifyTrace() {
    wantTrace = true;
}

// Implementación de la función SelectionSort
template <class Key>
void SelectionSort(std::vector<Key>& arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;

        if(wantTrace){
            std::cout << "Paso " << i + 1 << ": ";
            for (int k = 0; k < n; ++k) {
                if (k == i) std::cout << "| ";
                std::cout << arr[k] << " ";
            }
            std::cout << std::endl;
        }
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) {
            Key temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}

// Implementación de la función QuickSort
template <class Key>
void QuickSort(std::vector<Key>& arr, int low, int high) {
    int i = low;
    int j = high;
    Key pivot = arr[(i + j) / 2];
    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
        if (wantTrace) {
        std::cout << "Pivote: " << pivot << std::endl;
        std::cout << "Vector partido: ";
        for (int k = low; k <= high; ++k) {
            std::cout << arr[k] << " ";
        }
        std::cout << std::endl;
    }
        if (low < j) {
            QuickSort(arr, low, j);
        }
        if (i < high) {
            QuickSort(arr, i, high);
        }
    }
}

// Implementación de la función heapify (para HeapSort)
template <class Key>
void heapify(int i, std::vector<Key>& arr, int n) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (wantTrace) {
        std::cout << "m=" << largest << " ";
        for (int k = 0; k < n; ++k) {
            if (k == i) std::cout << " i=" << i << " ";
            std::cout << arr[k] << " ";
        }
        std::cout << std::endl;
    }
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
    
    }
}

// Implementación de la función HeapSort
template <class Key>
void HeapSort(std::vector<Key>& arr, int n) {
    for (int i = n/2; i >= 0; i--) {
        heapify(i, arr, n);
    }
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(0, arr, i);
    }
}

// Implementación de la función deltasort (para ShellSort)
template <class Key>
void deltasort(int delta, std::vector<Key>& arr, int n) {
    for (int i = delta; i < n; i++) {
        Key temp = arr[i];
        int j = i;
        while (j >= delta && arr[j - delta] > temp) {
            arr[j] = arr[j - delta];
            j -= delta;
        }
        arr[j] = temp;
    }
}

// Implementación de la función ShellSort
template <class Key>
void ShellSort(std::vector<Key>& arr, int n) {
    int delta = n;
    while (delta > 1) {
        if (wantTrace){
            std::cout << " | ";
            for (int k = 0; k < n; ++k) {
                std::cout << arr[k] << " | ";
            }
            std::cout << "  delta=" << delta << " ";
        }
        delta = delta / 2;
        deltasort(delta, arr, n);
        if (wantTrace){
            std::cout << "=> ";
            for (int k = 0; k < n; ++k) {
                std::cout << arr[k] << " | ";
            }
            std::cout << std::endl;
        }
    }
}

// Implementación de la función RadixSort
template <class Key>
void RadixSort(std::vector<Key>& arr, int n) {
    Key max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    for (int exp = 1; max / exp > 0; exp *= 10) {
        std::vector<Key> output(n);
        std::vector<int> count(10, 0);
        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        if (wantTrace){
            std::cout << "RadixSort paso con exp = " << exp << ": ";
            for (int i = 0; i < n; i++) {
                std::cout << output[i] << " ";
            }
            std::cout << std::endl;
        }
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
}

// Implementación de la función BinSort
template <class Key>
void BinSort (std::vector <Key>& arr, int n) {
    for (int i = 1; i < n; i++) {
        Key temp = arr[i];
        int ini = 0;
        int fin = i - 1;
        while (ini <= fin) {
            int m = (ini + fin) / 2;
            if (temp > arr[m]) {
                ini = m + 1;
            } else {
                fin = m - 1;
            }
        }
        for (int j = i - 1; j >= ini; j--) {
            arr[j + 1] = arr[j];
        }
        arr[ini] = temp;
    }
    if (wantTrace){
        std::cout << "BinSort paso: ";
        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
}

// Implementación de la función Mix (Para MergeSort)
template <class Key>
void Mix(std::vector <Key>& arr, int ini, int cen , int fin) {
    int n1 = cen - ini + 1;
    int n2 = fin - cen;
    std::vector <Key> L(n1);
    std::vector <Key> R(n2);
    for (int i = 0; i < n1; i++) {
        L[i] = arr[ini + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[cen + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = ini;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Implementación de la función MergeSort
template <class Key>
void MergeSort(std::vector <Key>& arr, int ini, int fin) {
    if (ini < fin) {
        int cen = (ini + fin) / 2;
        MergeSort(arr, ini, cen);
        MergeSort(arr, cen + 1, fin);
        Mix(arr, ini, cen, fin);
    }
}

