#include <iostream>
#include <chrono>
using namespace std;

void printArray(int arr[], int n, int paso) {
    cout << "Paso " << paso << ": ";

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << endl;
}

void insertionSort(int arr[], int n) {
    int paso = 0;

    printArray(arr, n, paso++);

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;

        printArray(arr, n, paso++);
    }
}

int main() {
    int arr[] = {5, 2, 9, 1, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Insertion Sort:" << endl;

    auto inicio = chrono::high_resolution_clock::now();

    insertionSort(arr, n);

    auto fin = chrono::high_resolution_clock::now();

    auto tiempo = chrono::duration_cast<chrono::microseconds>(fin - inicio);

    cout << "Tiempo de ejecucion: "
         << tiempo.count()
         << " microsegundos" << endl;

    return 0;
}