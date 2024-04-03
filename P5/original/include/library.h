#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

template <class Key>
void SelectionSort(std::vector<Key>& arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
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
        if (low < j) {
            QuickSort(arr, low, j);
        }
        if (i < high) {
            QuickSort(arr, i, high);
        }
    }
}

template <class Key>
void heapify(int i, std::vector<Key>& arr, int n) {
    while (2*i <= n) {
        int h1 = 2*i;
        int h2 = h1 + 1;
        int h;
        if (h1 == n){
            h = h1;
        } else if (arr[h1] > arr[h2]){
            h = h1;
        } else {
            h = h2;
        }
        if (arr[h] <= arr[i]){
            break;
        } else{
            std::swap(arr[i], arr[h]);
            i = h;
        }
    }
}

template <class Key>
void HeapSort(std::vector<Key>& arr, int n) {
    for (int i = n / 2; i > 0; i--) {
        heapify(i, arr, n);
    }
    for (int i = n; i > 1; i--) {
        std::swap(arr[1], arr[i]);
        heapify(1, arr, i - 1);
    }
}


