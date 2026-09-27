#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
using namespace std;

// Ordenamiento burbuja
void burbuja(vector<string>& nombres) {
    int n = nombres.size();
    int comparaciones = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparaciones++;
            if (nombres[j] > nombres[j + 1])
                swap(nombres[j], nombres[j + 1]);
        }
    }
    cout << "  Comparaciones burbuja: " << comparaciones << endl;
}

int main() {
    vector<string> nombres1 = {"Carlos", "Ana", "Luis", "Maria", "Pedro", "Zoe", "Bruno"};
    vector<string> nombres2 = nombres1;

    cout << "Lista original: ";
    for (string n : nombres1) cout << n << " ";
    cout << endl;
    cout << "----------------------------------------" << endl;

    // Burbuja
    auto inicio1 = chrono::high_resolution_clock::now();
    burbuja(nombres1);
    auto fin1 = chrono::high_resolution_clock::now();

    cout << "Ordenamiento burbuja: ";
    for (string n : nombres1) cout << n << " ";
    cout << endl;
    cout << "  Tiempo: " << chrono::duration_cast<chrono::nanoseconds>(fin1 - inicio1).count() << " ns" << endl;
    cout << "  Complejidad: O(n^2)" << endl;

    cout << "----------------------------------------" << endl;

    // sort() de la librería estándar
    auto inicio2 = chrono::high_resolution_clock::now();
    sort(nombres2.begin(), nombres2.end());
    auto fin2 = chrono::high_resolution_clock::now();

    cout << "Ordenamiento sort(): ";
    for (string n : nombres2) cout << n << " ";
    cout << endl;
    cout << "  Tiempo: " << chrono::duration_cast<chrono::nanoseconds>(fin2 - inicio2).count() << " ns" << endl;
    cout << "  Complejidad: O(n log n)" << endl;

    cout << "----------------------------------------" << endl;
    cout << "Conclusion: con n nombres, burbuja hace n*(n-1)/2 comparaciones O(n^2)" << endl;
    cout << "sort() usa introsort y hace aproximadamente n*log(n) comparaciones" << endl;

    return 0;
}