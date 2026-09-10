#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

void insertionSortNombres(vector<string>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        string key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    for (int iter = 1; iter <= 3; iter++) {
        int n;
        cout << "Ingrese la cantidad de elementos n para esta lista: ";
        cin >> n;

        vector<string> nombres(n);
        cout << "Ingrese los " << n << " nombres (pueden ser ordenados, inversos o aleatorios):\n";
        for (int i = 0; i < n; i++) {
            cin >> nombres[i];
        }

        auto inicio = chrono::high_resolution_clock::now();
        insertionSortNombres(nombres);
        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion = fin - inicio;

        cout << "\nLista ordenada:\n";
        for (const string& nombre : nombres) {
            cout << nombre << " ";
        }
        cout << "\n\n Tiempo de ejecucion: " << duracion.count() << " ms\n";
    }
    return 0;
}