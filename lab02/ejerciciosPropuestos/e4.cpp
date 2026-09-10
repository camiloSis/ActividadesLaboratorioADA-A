#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>
#include <algorithm>

using namespace std;

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
        }
    }
}

void evaluarOrdenamiento(vector<int> arr, string tipo) {
    auto inicio = chrono::high_resolution_clock::now();

    if (tipo == "insertion") {
        insertionSort(arr);
    } else if (tipo == "selection") {
        selectionSort(arr);
    }

    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = fin - inicio;

    cout << "Algoritmo: " << tipo << " | Elementos: " << arr.size() 
         << " | Tiempo: " << duracion.count() << " ms" << endl;
}

int main() {
    vector<int> tamanios = {1000, 5000, 10000};

    for (int tam : tamanios) {
        vector<int> datos(tam);
        generate(datos.begin(), datos.end(), []() { return rand() % 100000; });

        evaluarOrdenamiento(datos, "insertion");
        evaluarOrdenamiento(datos, "selection");
        cout << "-----------------------------------" << endl;
    }

    return 0;
}