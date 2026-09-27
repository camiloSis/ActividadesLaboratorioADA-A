#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Estudiante {
    string codigo;
    string nombre;
    float promedio;
};

void merge(vector<Estudiante>& arr, int izq, int mid, int der) {
    vector<Estudiante> left(arr.begin() + izq, arr.begin() + mid + 1);
    vector<Estudiante> right(arr.begin() + mid + 1, arr.begin() + der + 1);

    int i = 0, j = 0, k = izq;
    while (i < left.size() && j < right.size()) {
        if (left[i].promedio <= right[j].promedio) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

void mergesort(vector<Estudiante>& arr, int izq, int der) {
    if (izq < der) {
        int mid = (izq + der) / 2;
        mergesort(arr, izq, mid);
        mergesort(arr, mid + 1, der);
        merge(arr, izq, mid, der);
    }
}

int main() {
    int n;
    cout << "Ingrese cantidad de estudiantes: ";
    cin >> n;

    vector<Estudiante> estudiantes(n);
    for (int i = 0; i < n; i++) {
        cout << "\nEstudiante " << i + 1 << ":" << endl;
        cout << "Codigo: "; cin >> estudiantes[i].codigo;
        cout << "Nombre: "; cin >> estudiantes[i].nombre;
        cout << "Promedio: "; cin >> estudiantes[i].promedio;
    }

    mergesort(estudiantes, 0, n - 1);

    cout << "\nEstudiantes ordenados por promedio:\n";
    cout << "Codigo\t\tNombre\t\tPromedio\n";
    cout << "----------------------------------------\n";
    for (auto& e : estudiantes) {
        cout << e.codigo << "\t\t" << e.nombre << "\t\t" << e.promedio << "\n";
    }

    return 0;
}