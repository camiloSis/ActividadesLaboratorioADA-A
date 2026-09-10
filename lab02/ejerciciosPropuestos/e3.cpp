#include <iostream>
#include <vector>

using namespace std;

void selectionSortFloats(vector<float>& arr, int& comparaciones, int& intercambios) {
    int n = arr.size();
    comparaciones = 0;
    intercambios = 0;

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparaciones++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
            intercambios++;
        }
    }
}

int main() {
    vector<float> numeros = {15.4, 2.1, 99.8, 45.3, 12.0, 7.5};
    int comp = 0, inter = 0;

    selectionSortFloats(numeros, comp, inter);

    cout << "Arreglo ordenado: ";
    for (float f : numeros) cout << f << " ";
    cout << "\nNumero de comparaciones: " << comp;
    cout << "\nNumero de intercambios: " << inter << endl;

    return 0;
}