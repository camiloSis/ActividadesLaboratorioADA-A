#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
using namespace std;

void merge(vector<int>& arr, int izq, int mid, int der) {
    vector<int> left(arr.begin() + izq, arr.begin() + mid + 1);
    vector<int> right(arr.begin() + mid + 1, arr.begin() + der + 1);
    int i = 0, j = 0, k = izq;
    while (i < left.size() && j < right.size())
        arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

void mergesort(vector<int>& arr, int izq, int der) {
    if (izq < der) {
        int mid = (izq + der) / 2;
        mergesort(arr, izq, mid);
        mergesort(arr, mid + 1, der);
        merge(arr, izq, mid, der);
    }
}

int busquedaBinaria(vector<int>& arr, int objetivo) {
    int izq = 0, der = arr.size() - 1;
    while (izq <= der) {
        int mid = (izq + der) / 2;
        if (arr[mid] == objetivo) return mid;
        else if (arr[mid] < objetivo) izq = mid + 1;
        else der = mid - 1;
    }
    return -1;
}

int busquedaSecuencial(vector<int>& arr, int objetivo) {
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] == objetivo) return i;
    return -1;
}

int main() {
    int n;
    cout << "Ingrese n: ";
    cin >> n;

    vector<int> arr(n), arrOriginal(n);
    for (int i = 0; i < n; i++)
        arr[i] = arrOriginal[i] = rand() % 10000;

    int objetivo = arr[n / 2];

    // Mergesort + binaria
    auto inicio1 = chrono::high_resolution_clock::now();
    mergesort(arr, 0, n - 1);
    int pos1 = busquedaBinaria(arr, objetivo);
    auto fin1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo1 = fin1 - inicio1;

    // Secuencial sin ordenar
    auto inicio2 = chrono::high_resolution_clock::now();
    int pos2 = busquedaSecuencial(arrOriginal, objetivo);
    auto fin2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo2 = fin2 - inicio2;

    cout << "\nBuscando: " << objetivo << endl;
    cout << "----------------------------------------\n";
    cout << "Mergesort O(n log n) + Binaria O(log n):\n";
    cout << "  Encontrado en posicion: " << pos1 << endl;
    cout << "  Tiempo total: " << tiempo1.count() << " ms\n";
    cout << "  Complejidad total: O(n log n)\n";
    cout << "----------------------------------------\n";
    cout << "Busqueda secuencial O(n):\n";
    cout << "  Encontrado en posicion: " << pos2 << endl;
    cout << "  Tiempo total: " << tiempo2.count() << " ms\n";
    cout << "  Complejidad total: O(n)\n";
    cout << "----------------------------------------\n";
    cout << "Nota: secuencial es mejor para una sola busqueda,\n";
    cout << "pero mergesort+binaria es mejor para multiples busquedas\n";

    return 0;
}