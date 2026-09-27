#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

int particionFija(vector<float>& arr, int izq, int der) {
    float pivot = arr[der];
    int i = izq - 1;
    for (int j = izq; j < der; j++) {
        if (arr[j] <= pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[der]);
    return i + 1;
}

void quicksortFijo(vector<float>& arr, int izq, int der) {
    if (izq < der) {
        int pi = particionFija(arr, izq, der);
        quicksortFijo(arr, izq, pi - 1);
        quicksortFijo(arr, pi + 1, der);
    }
}

// Pivote aleatorio
int particionAleatoria(vector<float>& arr, int izq, int der) {
    int pivotIdx = izq + rand() % (der - izq + 1);
    swap(arr[pivotIdx], arr[der]);
    return particionFija(arr, izq, der);
}

void quicksortAleatorio(vector<float>& arr, int izq, int der) {
    if (izq < der) {
        int pi = particionAleatoria(arr, izq, der);
        quicksortAleatorio(arr, izq, pi - 1);
        quicksortAleatorio(arr, pi + 1, der);
    }
}

int main() {
    srand(time(0));
    int n = 10000;

    vector<float> arr1(n), arr2(n);
    for (int i = 0; i < n; i++) {
        arr1[i] = arr2[i] = (float)(rand() % 10000) / 100.0;
    }

    // Pivote fijo
    auto inicio1 = chrono::high_resolution_clock::now();
    quicksortFijo(arr1, 0, n - 1);
    auto fin1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo1 = fin1 - inicio1;

    // Pivote aleatorio
    auto inicio2 = chrono::high_resolution_clock::now();
    quicksortAleatorio(arr2, 0, n - 1);
    auto fin2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo2 = fin2 - inicio2;

    cout << "Quicksort con " << n << " elementos:\n";
    cout << "----------------------------------------\n";
    cout << "Pivote fijo:     " << tiempo1.count() << " ms  O(n^2) peor caso\n";
    cout << "Pivote aleatorio: " << tiempo2.count() << " ms  O(n log n) promedio\n";
    cout << "----------------------------------------\n";
    cout << "Pivote fijo es mejor cuando el arreglo ya esta casi ordenado\n";
    cout << "Pivote aleatorio es mejor para arreglos aleatorios o inversamente ordenados\n";

    return 0;
}