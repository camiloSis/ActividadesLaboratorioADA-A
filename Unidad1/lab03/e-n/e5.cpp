#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

struct Producto {
    string codigo;
    string nombre;
    float precio;
};

vector<Producto> leerArchivo(string ruta) {
    vector<Producto> productos;
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo\n";
        return productos;
    }
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Producto p;
        string precioStr;
        
        getline(ss, p.codigo, ',');
        getline(ss, p.nombre, ',');
        getline(ss, precioStr, ',');
        
        p.precio = stof(precioStr); // Convierte texto a float
        productos.push_back(p);
    }
    archivo.close();
    return productos;
}

// Mergesort
void mergeProductos(vector<Producto>& arr, int izq, int mid, int der) {
    vector<Producto> left(arr.begin() + izq, arr.begin() + mid + 1);
    vector<Producto> right(arr.begin() + mid + 1, arr.begin() + der + 1);
    int i = 0, j = 0, k = izq;
    while (i < left.size() && j < right.size())
        arr[k++] = (left[i].precio >= right[j].precio) ? left[i++] : right[j++];
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

void mergesortProductos(vector<Producto>& arr, int izq, int der) {
    if (izq < der) {
        int mid = (izq + der) / 2;
        mergesortProductos(arr, izq, mid);
        mergesortProductos(arr, mid + 1, der);
        mergeProductos(arr, izq, mid, der);
    }
}

// Quicksort
int particionProductos(vector<Producto>& arr, int izq, int der) {
    float pivot = arr[der].precio;
    int i = izq - 1;
    for (int j = izq; j < der; j++)
        if (arr[j].precio >= pivot) swap(arr[++i], arr[j]);
    swap(arr[i + 1], arr[der]);
    return i + 1;
}

void quicksortProductos(vector<Producto>& arr, int izq, int der) {
    if (izq < der) {
        int pi = particionProductos(arr, izq, der);
        quicksortProductos(arr, izq, pi - 1);
        quicksortProductos(arr, pi + 1, der);
    }
}

void imprimirProductos(vector<Producto>& arr) {
    cout << "Codigo\t\tNombre\t\tPrecio\n";
    cout << "----------------------------------------\n";
    for (auto& p : arr)
        cout << p.codigo << "\t\t" << p.nombre << "\t\t" << p.precio << "\n";
}

int main() {
    vector<Producto> productos1 = leerArchivo("productos.txt");
    vector<Producto> productos2 = productos1;

    if (productos1.empty()) return 1;

    // Mergesort
    auto inicio1 = chrono::high_resolution_clock::now();
    mergesortProductos(productos1, 0, productos1.size() - 1);
    auto fin1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo1 = fin1 - inicio1;

    cout << "Ordenado con Mergesort (mayor a menor precio):\n";
    imprimirProductos(productos1);
    cout << "Tiempo: " << tiempo1.count() << " ms\n\n";

    // Quicksort
    auto inicio2 = chrono::high_resolution_clock::now();
    quicksortProductos(productos2, 0, productos2.size() - 1);
    auto fin2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo2 = fin2 - inicio2;

    cout << "Ordenado con Quicksort (mayor a menor precio):\n";
    imprimirProductos(productos2);
    cout << "Tiempo: " << tiempo2.count() << " ms\n";

    return 0;
}