#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

struct Libro {
    string codigo;
    string titulo;
    int paginas;
};

void cargarDatos(const string& filename, vector<Libro>& lista) {
    ifstream archivo(filename);
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string cod, nom, pagStr;
        if (getline(ss, cod, ',') && getline(ss, nom, ',') && getline(ss, pagStr, ',')) {
            lista.push_back({cod, nom, stoi(pagStr)});
        }
    }
}

void insertionSortDesc(vector<Libro>& arr, long long& comp, long long& inter) {
    int n = arr.size();
    comp = 0; inter = 0;
    for (int i = 1; i < n; i++) {
        Libro key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comp++;
            if (arr[j].paginas < key.paginas) {
                arr[j + 1] = arr[j];
                inter++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

void selectionSortDesc(vector<Libro>& arr, long long& comp, long long& inter) {
    int n = arr.size();
    comp = 0; inter = 0;
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            comp++;
            if (arr[j].paginas > arr[maxIdx].paginas) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            swap(arr[i], arr[maxIdx]);
            inter++;
        }
    }
}

void exportarCSV(const string& filename, const vector<Libro>& lista) {
    ofstream archivo(filename);
    archivo << "Codigo,Titulo,Paginas\n";
    for (const auto& l : lista) {
        archivo << l.codigo << "," << l.titulo << "," << l.paginas << "\n";
    }
}

int main() {
    vector<Libro> libros;
    cargarDatos("libros.txt", libros);

    if (libros.empty()) {
        cout << "Error: No se encontraron datos en libros.txt" << endl;
        return 1;
    }

    vector<Libro> librosIns = libros;
    vector<Libro> librosSel = libros;

    long long compIns = 0, interIns = 0;
    long long compSel = 0, interSel = 0;

    auto t1 = chrono::high_resolution_clock::now();
    insertionSortDesc(librosIns, compIns, interIns);
    auto t2 = chrono::high_resolution_clock::now();
    double tiempoIns = chrono::duration<double, milli>(t2 - t1).count();

    t1 = chrono::high_resolution_clock::now();
    selectionSortDesc(librosSel, compSel, interSel);
    t2 = chrono::high_resolution_clock::now();
    double tiempoSel = chrono::duration<double, milli>(t2 - t1).count();

    cout << "Insertion Sort:\n";
    cout << "- Comparaciones: " << compIns << "\n";
    cout << "- Intercambios: " << interIns << "\n";
    cout << "- Tiempo: " << tiempoIns << " ms\n\n";

    cout << "Selection Sort:\n";
    cout << "- Comparaciones: " << compSel << "\n";
    cout << "- Intercambios: " << interSel << "\n";
    cout << "- Tiempo: " << tiempoSel << " ms\n";

    exportarCSV("libros_ordenados.csv", librosIns);
    cout << "\nArchivo 'libros_ordenados.csv' generado exitosamente.\n";

    return 0;
}